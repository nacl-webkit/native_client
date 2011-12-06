#!/usr/bin/python
# Copyright (c) 2011 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
#
# IMPORTANT NOTE: If you make local mods to this file, you must run:
#   %  tools/llvm/utman.sh driver
# in order for them to take effect in the scons build.  This command
# updates the copy in the toolchain/ tree.
#

from driver_tools import *

EXTRA_ENV = {
  'PIC'           : '0',

  # Use the IRT shim by default on x86-64. This can be disabled with an
  # explicit flag (--noirtshim) or via -nostdlib.
  'USE_IRT_SHIM': '${ARCH==X8664 ? 1 : 0}',

  # Flags for pnacl-nativeld
  'LD_FLAGS': '${STATIC ? -static : ${SHARED ? -shared}}',

  'STATIC'        : '0',
  'SHARED'        : '0',
  'STDLIB'        : '1',
  'DEFAULTLIBS'   : '1',

  'INPUTS'        : '',
  'OUTPUT'        : '',
  'OUTPUT_TYPE'   : '',

  # Library Strings
  'EMITMODE'         : '${STATIC ? static : ${SHARED ? shared : dynamic}}',

  'LD_ARGS' : '${STDLIB ? ' +
              '${LD_ARGS_%LIBMODE%_%EMITMODE%} : ${LD_ARGS_nostdlib}}',

  'LD_ARGS_nostdlib': '-nostdlib ${ld_inputs}',

  'LD_ARGS_IRT_SHIM':
    '${USE_IRT_SHIM ? -lpnacl_irt_shim  -entry=_pnacl_wrapper_start}',

  # These are just the dependencies in the native link.
  # TODO(pdox): To simplify translation, reduce from 4 to 2 cases.
  # BUG= http://code.google.com/p/nativeclient/issues/detail?id=2423
  'LD_ARGS_newlib_static':
    '${LD_ARGS_IRT_SHIM} -l:crtbegin.o ' +
    '${DEFAULTLIBS ? --start-group ${ld_inputs} -lgcc_eh -lgcc --end-group} ' +
    '-l:libcrt_platform.a -l:crtend.o',

  'LD_ARGS_glibc_static' :
     '${LD_ARGS_IRT_SHIM} -l:crti.o -l:crtbeginT.o ${ld_inputs} ' +
     '${DEFAULTLIBS ? ${GLIBC_HACK} --start-group -lgcc -lgcc_eh -lc ' +
     '--end-group} -l:crtend.o -l:crtn.o',

  'LD_ARGS_glibc_shared' :
     '--eh-frame-hdr -shared -l:crti.o -l:crtbeginS.o ' +
     '${ld_inputs} ${DEFAULTLIBS ? ${SDK_HACK} ${GLIBC_HACK} ${DSO_HACK} ' +
     '-lgcc -lgcc_s} -l:crtendS.o -l:crtn.o',

  'LD_ARGS_glibc_dynamic':
    '--eh-frame-hdr ${LD_ARGS_IRT_SHIM} -l:crti.o -l:crtbegin.o ' +
    '${ld_inputs} ${DEFAULTLIBS ? ${SDK_HACK} ${GLIBC_HACK} ${DSO_HACK} ' +
    '-lgcc -lgcc_s} -l:crtend.o -l:crtn.o',

  # Because of ABI and symbol versioning issues, these still need to
  # be included directly in the native link.
  # BUG= http://code.google.com/p/nativeclient/issues/detail?id=577
  # BUG= http://code.google.com/p/nativeclient/issues/detail?id=2089
  'GLIBC_HACK': '--as-needed -lstdc++ -lm --no-as-needed -lc -lpthread',
  'DSO_HACK'  : '-l:ld-2.9.so',
  # BUG= http://code.google.com/p/nativeclient/issues/detail?id=2451
  'SDK_HACK'  : '',
  # END HACK

  # Intermediate variable LLCVAR is used for delaying evaluation.
  'LLCVAR'        : '${SANDBOXED ? LLC_SB : LLVM_LLC}',
  'LLC'           : '${%LLCVAR%}',

  'TRIPLE'      : '${TRIPLE_%ARCH%}',
  'TRIPLE_ARM'  : 'armv7a-none-nacl-gnueabi',
  'TRIPLE_X8632': 'i686-none-nacl-gnu',
  'TRIPLE_X8664': 'x86_64-none-nacl-gnu',

  'LLC_FLAGS_COMMON': '-asm-verbose=false ' +
                      '-tail-merge-threshold=50 ' +
                      '${PIC ? -relocation-model=pic} ' +
                      '${PIC && ARCH==X8664 && LIBMODE_NEWLIB ? ' +
                      '  -force-tls-non-pic }',
  'LLC_FLAGS_ARM'    :
    # The following options might come in handy and are left here as comments:
    # TODO(robertm): describe their purpose
    #     '-soft-float -aeabi-calls -sfi-zero-mask',
    # NOTE: we need a fairly high fudge factor because of
    # some vfp instructions which only have a 9bit offset
    ('-arm-reserve-r9 -sfi-disable-cp -arm_static_tls ' +
     '-sfi-load -sfi-store -sfi-stack -sfi-branch -sfi-data ' +
     '-no-inline-jumptables'),

  'LLC_FLAGS_X8632' : '',
  'LLC_FLAGS_X8664' : '',

  # LLC flags which set the target and output type.
  # These are handled separately by libLTO.
  'LLC_FLAGS_TARGET' : '-march=${LLC_MARCH} -mcpu=${LLC_MCPU_%ARCH%} ' +
                       '-mtriple=${TRIPLE} -filetype=${filetype}',
  'LLC_FLAGS_BASE': '${LLC_FLAGS_COMMON} ${LLC_FLAGS_%ARCH%}',
  'LLC_FLAGS'     : '${LLC_FLAGS_TARGET} ${LLC_FLAGS_BASE}',

  'LLC_MARCH'       : '${LLC_MARCH_%ARCH%}',
  'LLC_MARCH_ARM'   : 'arm',
  'LLC_MARCH_X8632' : 'x86',
  'LLC_MARCH_X8664' : 'x86-64',

  'LLC_MCPU'        : '${LLC_MCPU_%ARCH%}',
  'LLC_MCPU_ARM'    : 'cortex-a8',
  'LLC_MCPU_X8632'  : 'pentium4',
  'LLC_MCPU_X8664'  : 'core2',

  'RUN_LLC'       : '${LLC} ${LLC_FLAGS} ${input} -o ${output}',
}
env.update(EXTRA_ENV)


TranslatorPatterns = [
  ( '-o(.+)',          "env.set('OUTPUT', pathtools.normalize($0))"),
  ( ('-o', '(.+)'),    "env.set('OUTPUT', pathtools.normalize($0))"),

  ( '-S',              "env.set('OUTPUT_TYPE', 's')"), # Stop at .s
  ( '-c',              "env.set('OUTPUT_TYPE', 'o')"), # Stop at .o

  # Expose a very limited set of llc flags. Used primarily for
  # the shared lib ad-hoc tests, c.f. tests/pnacl_ld_example
  ( '(-sfi-.+)',       "env.append('LLC_FLAGS', $0)"),
  ( '(-mtls-use-call)',  "env.append('LLC_FLAGS', $0)"),

  # If translating a .pexe which was linked statically against
  # glibc, then you must do pnacl-translate -static. This will
  # be removed once GLibC is actually statically linked.
  ( '-static',         "env.set('STATIC', '1')"),
  ( '-shared',         "env.set('SHARED', '1')"),
  ( '-nostdlib',       "env.set('STDLIB', '0')"),
  ( '-nodefaultlibs',  "env.set('DEFAULTLIBS', '0')"),

  ( '--noirtshim',      "env.set('USE_IRT_SHIM', '0')"),

  ( '-rpath-link=(.+)', "env.append('LD_FLAGS', '-L'+$0)"),

  ( '-fPIC',           "env.set('PIC', '1')"),

  ( '-Wl,(.*)',        "env.append('LD_FLAGS', *($0).split(','))"),

  ( '(-.*)',            UnrecognizedOption),

  ( '(.*)',            "env.append('INPUTS', pathtools.normalize($0))"),
]

def main(argv):
  ParseArgs(argv, TranslatorPatterns)

  if env.getbool('SHARED') and env.getbool('STATIC'):
    Log.Fatal('Cannot mix -static and -shared')

  GetArch(required = True)

  inputs = env.get('INPUTS')
  output = env.getone('OUTPUT')

  if len(inputs) == 0:
    Log.Fatal("No input files")

  # If there's a bitcode file, find it.
  bcfiles = filter(IsBitcode, inputs)
  if len(bcfiles) > 1:
    Log.Fatal('Expecting at most 1 bitcode file')

  if bcfiles:
    bcfile = bcfiles[0]
    bctype = FileType(bcfile)
    has_bitcode = True
    # Placeholder for actual object file
    inputs = ListReplace(inputs, bcfile, '__BITCODE__')
    env.set('INPUTS', *inputs)
  else:
    bcfile = None
    has_bitcode = False

  # Determine the output type, in this order of precedence:
  # 1) Output type can be specified on command-line (-S, -c, -shared, -static)
  # 2) If bitcode file given, use it's output type. (pso->so, pexe->nexe, po->o)
  # 3) Otherwise, assume nexe output.
  output_type = env.getone('OUTPUT_TYPE')
  if output_type == '':
    if env.getbool('SHARED'):
      output_type = 'so'
    elif env.getbool('STATIC'):
      output_type = 'nexe'
    elif bcfile:
      DefaultOutputTypes = {
        'pso' : 'so',
        'pexe': 'nexe',
        'po'  : 'o',
      }
      output_type = DefaultOutputTypes[bctype]
    else:
      output_type = 'nexe'

  # Default to -static for newlib.
  # TODO(pdox): This shouldn't be necessary.
  # BUG= http://code.google.com/p/nativeclient/issues/detail?id=2423
  if env.getbool('LIBMODE_NEWLIB'):
    if env.getbool('SHARED'):
      Log.Fatal('Cannot handle -shared with newlib toolchain')
    env.set('STATIC', '1')

  if bcfile:
    ApplyBitcodeConfig(bcfile, bctype)

  if output == '':
    if bcfile:
      output = DefaultOutputName(bcfile, output_type)
    else:
      output = pathtools.normalize('a.out')

  tng = TempNameGen(inputs + bcfiles, output)
  chain = DriverChain(bcfile, output, tng)
  SetupChain(chain, has_bitcode, output_type)
  chain.run()
  return 0

def ApplyBitcodeConfig(bcfile, bctype):
  if bctype == 'pso':
    env.set('SHARED', '1')

  if env.getbool('SHARED'):
    env.set('PIC', '1')

  # Normally, only pso files need to be translated with PIC, but since we
  # are linking executables with unresolved symbols, dynamic nexe's
  # also need to be PIC to be able to generate the correct relocations.
  # BUG= http://code.google.com/p/nativeclient/issues/detail?id=2351
  if bctype == 'pexe' and env.getbool('LIBMODE_GLIBC'):
    env.set('PIC', '1')
    env.append('LD_FLAGS', '--unresolved-symbols=ignore-all')

  # Read the bitcode metadata to extract library
  # dependencies and SOName.
  metadata = GetBitcodeMetadata(bcfile)
  for lib in metadata['NeedsLibrary']:
    env.append('LD_FLAGS', '--add-extra-dt-needed=' + lib)
    # BUG= http://code.google.com/p/nativeclient/issues/detail?id=2451
    direct_libs = ['srpc','ppapi_cpp']
    for libname in direct_libs:
      if lib == 'lib'+libname+'.so':
        env.append('SDK_HACK', '-l'+libname)

  if bctype == 'pso':
    soname = metadata['SOName']
    if soname:
      env.append('LD_FLAGS', '-soname=' + soname)

def SetupChain(chain, has_bitcode, output_type):
  assert output_type in ('o','s','so','nexe')

  if has_bitcode:
    if output_type == 's' or not env.getbool('MC_DIRECT'):
      chain.add(RunLLC, 's', filetype='asm')
      if output_type == 's':
        return
      chain.add(RunAS, 'o')
    else:
      chain.add(RunLLC, 'o', filetype='obj')
    if output_type == 'o':
      return

  if output_type == 'so':
    chain.add(RunLD, 'so')
  elif output_type == 'nexe':
    chain.add(RunLD, 'nexe')

def RunAS(infile, outfile):
  RunDriver('pnacl-as', [infile, '-o', outfile])

def ListReplace(items, old, new):
  ret = []
  for k in items:
    if k == old:
      ret.append(new)
    else:
      ret.append(k)
  return ret

def RunLD(infile, outfile):
  inputs = env.get('INPUTS')
  if infile:
    inputs = ListReplace(inputs, '__BITCODE__', '--shm=' + infile)
  env.set('ld_inputs', *inputs)
  args = env.get('LD_ARGS') + ['-o', outfile]
  args += env.get('LD_FLAGS')
  RunDriver('pnacl-nativeld', args)


def RunLLC(infile, outfile, filetype):
  UseSRPC = env.getbool('SANDBOXED') and env.getbool('SRPC')
  # For now, sel_universal doesn't properly support dynamic sb translator
  if env.getbool('SANDBOXED') and env.getbool('SB_DYNAMIC'):
    CheckTranslatorPrerequisites()
    UseSRPC = False
  env.push()
  env.setmany(input=infile, output=outfile, filetype=filetype)
  if UseSRPC:
    RunLLCSRPC()
  else:
    RunWithLog("${RUN_LLC}")
  env.pop()
  return 0

def RunLLCSRPC():
  CheckTranslatorPrerequisites()
  infile = env.getone("input")
  outfile = env.getone("output")
  flags = env.get("LLC_FLAGS")
  script = MakeSelUniversalScriptForLLC(infile, outfile, flags)

  RunWithLog('${SEL_UNIVERSAL_PREFIX} ${SEL_UNIVERSAL} ' +
             '${SEL_UNIVERSAL_FLAGS} -- ${LLC_SRPC}',
             stdin=script, echo_stdout = False, echo_stderr = False)

def MakeSelUniversalScriptForLLC(infile, outfile, flags):
  script = []
  script.append('readonly_file myfile %s' % infile)
  script.append('readwrite_file objfile %s' % outfile)
  script.append('pnacl_emu_initialize')
  script.append('install_upcalls lookup_service_string dummy_channel')
  script.append('rpc StartLookupService s("${lookup_service_string}") *')
  # command_line is a NUL (\x00) terminated sequence.
  kTerminator = '\0'
  command_line = kTerminator.join(['llc'] + flags) + kTerminator
  command_line_escaped = command_line.replace(kTerminator, '\\x00')
  script.append('rpc Run C(%d,%s) h(myfile) h(objfile) * i() s() s()' %
                (len(command_line), command_line_escaped))
  script.append('echo "llc complete"')
  script.append('')
  return '\n'.join(script)

if __name__ == "__main__":
  DriverMain(main)
