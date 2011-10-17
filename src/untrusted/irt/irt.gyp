# Copyright (c) 2011 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

{
  'includes': [
    '../../../build/common.gypi',
  ],
  'variables': {
    'irt_sources': [
# irt_support_sources
      'irt_entry.c',
      'irt_malloc.c',
      'irt_private_pthread.c',
      'irt_private_tls.c',
# irt_common_interfaces
      'irt_basic.c',
      'irt_fdio.c',
      'irt_filename.c',
      'irt_memory.c',
      'irt_dyncode.c',
      'irt_thread.c',
      'irt_mutex.c',
      'irt_cond.c',
      'irt_sem.c',
      'irt_tls.c',
      'irt_blockhook.c',
# support_srcs
      '../pthread/nc_mutex.c',
      '../pthread/nc_condvar.c',
      '../pthread/nc_token.c',
      '../nacl/sys_private.c',
    ],
    'irt_nonbrowser': [
      'irt_interfaces.c',
      'irt_core_resource.c',
    ],
    'irt_browser': [
      'irt_interfaces_ppapi.c',
      'irt_entry_ppapi.c',
      'irt_ppapi.c',
      'irt_manifest.c',
    ],
  },
  'conditions': [
    ['disable_untrusted==0 and target_arch!="arm"', {
      'targets': [
        {
          'target_name': 'irt_core_nexe',
          'type': 'none',
          'variables': {
            'nexe_target': 'irt_core',
            'build_glibc': 0,
            'build_newlib': 1,
            'suffix': '_,mainarch,subarch,nexe',
            'sources': ['<@(irt_sources)', '<@(irt_nonbrowser)'],
          },
          'conditions': [
            ['target_arch=="x64" or target_arch == "ia32"', {
              'variables': {
                'link_flags': [
                  '-Wl,--section-start,.rodata=0x3ef00000',
                  '-Wl,-Ttext-segment=0x0fc00000',
                ],
              },
            }],
          ],
          'dependencies': [
            '<(DEPTH)/native_client/tools.gyp:prep_toolchain',
            '<(DEPTH)/native_client/src/untrusted/nacl/nacl.gyp:nacl_lib_newlib',
          ],
        },
        {
          'target_name': 'irt_browser_lib',
          'type': 'none',
          'variables': {
            'nlib_target': 'libirt_browser.a',
            'build_glibc': 0,
            'build_newlib': 1,
            'sources': ['<@(irt_sources)', '<@(irt_browser)'],
          },
          'conditions': [
            ['target_arch == "x64" or target_arch == "ia32"', {
              'variables': {
                'link_flags': [
                  '-r',
                  '-nostartfiles',
                ],
              },
            }],
          ],
          'dependencies': [
            '<(DEPTH)/native_client/tools.gyp:prep_toolchain',
            '<(DEPTH)/native_client/src/untrusted/nacl/nacl.gyp:nacl_lib',
            '<(DEPTH)/native_client/src/shared/platform/platform.gyp:platform_lib',
          ],
        },
      ],
    }],
  ],
}