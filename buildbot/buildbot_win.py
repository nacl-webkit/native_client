#!/usr/bin/python
# Copyright (c) 2011 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

import os.path
import sys

from buildbot_lib import *

# Windows-specific environment manipulation
def SetupWindowsEnvironment(context):
  context.SetEnv('GYP_MSVS_VERSION', '2008')

  # Blow away path for now if on the bots (to be more hermetic).
  if os.environ.get('BUILDBOT_SLAVENAME'):
    paths = [
        r'c:\b\depot_tools',
        r'c:\b\depot_tools\python_bin',
        r'c:\b\build_internal\tools',
        r'e:\b\depot_tools',
        r'e:\b\depot_tools\python_bin',
        r'e:\b\build_internal\tools',
        r'C:\WINDOWS\system32',
        r'C:\WINDOWS\system32\WBEM',
        ]
    context.SetEnv('PATH', os.pathsep.join(paths))

  # Poke around looking for MSVC.  We should do something more principled in
  # the future.

  # The name of Program Files can differ, depending on the bittage of Windows.
  program_files = r'c:\Program Files (x86)'
  if not os.path.exists(program_files):
    program_files = r'c:\Program Files'
    if not os.path.exists(program_files):
      raise Exception('Cannot find the Program Files directory!')

  # The location of MSVC can differ depending on the version.
  msvc_locs = [
      # TODO(ncbray) use msvc 10.  This will require changing GYP_MSVS_VERSION.
      #('Microsoft Visual Studio 10.0', 'VS100COMNTOOLS'),
      ('Microsoft Visual Studio 9.0', 'VS90COMNTOOLS'),
      ('Microsoft Visual Studio 8.0', 'VS80COMNTOOLS'),
  ]

  for dirname, comntools_var in msvc_locs:
    msvc = os.path.join(program_files, dirname)
    if os.path.exists(msvc):
      break
  else:
    # The break statement did not execute.
    raise Exception('Cannot find MSVC!')

  # Put MSVC in the path.
  vc = os.path.join(msvc, 'VC')
  comntools = os.path.join(msvc, 'Common7', 'Tools')
  perf = os.path.join(msvc, 'Team Tools', 'Performance Tools')
  context.SetEnv('PATH', os.pathsep.join([
      context.GetEnv('PATH'),
      vc,
      comntools,
      perf]))

  # SCons needs this variable to find vsvars.bat.
  # The end slash is needed because the batch files expect it.
  context.SetEnv(comntools_var, comntools + '\\')

  # This environment variable will SCons to print debug info while it searches
  # for MSVC.
  context.SetEnv('SCONS_MSCOMMON_DEBUG', '-')

  # Needed for finding devenv.
  context['msvc'] = msvc


def PartialSDK(context, platform):
  args = ['--download', 'extra_sdk_update_header', 'extra_sdk_update']
  if not context['use_glibc']:
    args.append('install_libpthread')
  SCons(
      context,
      mode=['nacl_extra_sdk'],
      platform=platform,
      parallel=True,
      args=args)


def BuildScript(status, context):
  inside_toolchain = context['inside_toolchain']
  do_integration_tests = not context['use_glibc'] and not inside_toolchain
  do_dso_tests = context['use_glibc'] and not inside_toolchain

  # If we're running browser tests on a 64-bit Windows machine, build a 32-bit
  # plugin.
  need_plugin_32 = context['bits'] == '64' and not inside_toolchain

  # Clean out build directories.
  with Step('clobber', status):
    RemoveDirectory(r'scons-out')
    RemoveDirectory(r'build\Debug')
    RemoveDirectory(r'build\Release')
    RemoveDirectory(r'build\Debug-Win32')
    RemoveDirectory(r'build\Release-Win32')
    RemoveDirectory(r'build\Debug-x64')
    RemoveDirectory(r'build\Release-x64')

  with Step('cleanup_temp', status):
    # Picking out drive letter on which the build is happening so we can use
    # it for the temp directory.
    build_drive = os.path.splitdrive(os.path.abspath(__file__))[0]
    tmp_dir = os.path.join(build_drive, os.path.sep + 'temp')
    context.SetEnv('TEMP', tmp_dir)
    context.SetEnv('TMP', tmp_dir)
    print 'Making sure %s exists...' % tmp_dir
    EnsureDirectoryExists(tmp_dir)
    print 'Cleaning up the contents of %s...' % tmp_dir
    TryToCleanContents(tmp_dir)

  # Skip over hooks and partial_sdk when run inside the toolchain
  # build because partial_sdk would overwrite the toolchain build.
  if inside_toolchain:
    with Step('gyp_generate_only', status):
      Command(
          context,
          cmd=[
              sys.executable,
              'native_client/build/gyp_nacl',
              'native_client/build/all.gyp',
              ],
          cwd='..')
  else:
    with Step('gclient_runhooks', status):
      Command(context, cmd=['gclient.bat', 'runhooks', '--force'])

    # On windows 64 we build a 32-bit plugin for integration tests.
    # In this case, we'll also need to run a 32-bit partial SDK.
    if context['bits'] == '32' or need_plugin_32:
      with Step('partial_sdk_32', status):
        PartialSDK(context, platform='x86-32')
    if context['bits'] == '64':
      with Step('partial_sdk_64', status):
        PartialSDK(context, platform='x86-64')

  # Make sure out Gyp build is working.
  with Step('gyp_compile', status):
    Command(
        context,
        cmd=[
            os.path.join(context['msvc'], 'Common7', 'IDE', 'devenv.com'),
            r'build\all.sln',
            '/build', context['gyp_mode']
            ])

  # The main compile step.
  with Step('scons_compile', status):
    SCons(context, parallel=True, args=[])

  if need_plugin_32:
    with Step('plugin_compile_32', status):
      SCons(context, platform='x86-32', parallel=True, args=['plugin'])

  ### BEGIN tests ###
  with Step('small_tests', status, halt_on_fail=False):
    SCons(context, args=['small_tests'])

  # Skip these tests to save time.
  if not context['use_glibc']:
    with Step('medium_tests', status, halt_on_fail=False):
      SCons(context, args=['medium_tests'])
    with Step('large_tests', status, halt_on_fail=False):
      SCons(context, args=['large_tests'])

  if do_integration_tests:
    with Step('chrome_browser_tests', status, halt_on_fail=False):
      SCons(context, args=['SILENT=1', 'chrome_browser_tests'])

    plugin = 'ppGoogleNaClPlugin.dll'
    if context['bits'] == '32':
      sel_ldr = 'sel_ldr.exe'
    else:
      sel_ldr = 'sel_ldr64.exe'
    with Step('chrome_browser_tests using GYP', status, halt_on_fail=False):
      SCons(
          context,
          args=[
              r'force_ppapi_plugin=build\%s\%s' % (context['gyp_mode'], plugin),
              r'force_sel_ldr=build\%s\%s' % (context['gyp_mode'], sel_ldr),
              'SILENT=1',
              'chrome_browser_tests',
              ])

    # TODO(mcgrathr): Drop support for non-IRT builds and remove this entirely.
    # See http://code.google.com/p/nativeclient/issues/detail?id=1691
    with Step('chrome_browser_tests without IRT', status, halt_on_fail=False):
      SCons(context, args=['SILENT=1', 'irt=0', 'chrome_browser_tests'])


    with Step('pyauto_tests', status, halt_on_fail=False):
      SCons(context, args=['SILENT=1', 'pyauto_tests'])

  if do_dso_tests:
    with Step('dynamic_library_browser_tests', status, halt_on_fail=False):
      SCons(context, args=['SILENT=1', 'dynamic_library_browser_tests'])
  ### END tests ###


def Main():
  # TODO(ncbray) make buildbot scripts composable to support toolchain use case.
  status = BuildStatus()
  context = BuildContext()
  ParseStandardCommandLine(context)
  SetupWindowsEnvironment(context)
  RunBuild(BuildScript, status, context)


if __name__ == '__main__':
  Main()
