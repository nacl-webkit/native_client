#!/bin/bash
# Copyright (c) 2011 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

######################################################################
######################################################################
#
#                               < CONFIG >
#
######################################################################
######################################################################
#@ This script install and runs the gnu gcc toolchain testsuite against
#@ various nacl and and non-nacl toolchains.
#@
######################################################################
# Config
######################################################################

set -o nounset
set -o errexit

readonly TEST_ROOT=${TEST_ROOT:-/tmp/nacl_compiler_test}
readonly TEST_TARBALL_URL=${TEST_TARBALL_URL:-http://gcc.petsads.us/releases/gcc-4.6.1/gcc-testsuite-4.6.1.tar.bz2}

readonly TEST_PATH_C=${TEST_ROOT}/gcc-4.6.1/gcc/testsuite/gcc.c-torture/execute
readonly TEST_PATH_CPP=${TEST_ROOT}/gcc-4.6.1/gcc/testsuite/g++.dg
######################################################################
######################################################################
#
#                               < HELPERS >
#
######################################################################
######################################################################


Banner() {
  echo "######################################################################"
  echo "$@"
  echo "######################################################################"
}


SubBanner() {
  echo "......................................................................"
  echo "$@"
  echo "......................................................................"
}


DownloadOrCopy() {
   if [[ -f "$2" ]] ; then
     echo "$2 already in place"
   elif [[ $1 =~  'http://' ]] ; then
     SubBanner "downloading from $1"
     wget $1 -O $2
   else
     SubBanner "copying from $1"
     cp $1 $2
   fi
 }

######################################################################
######################################################################
#
#                               < ACTIONS >
#
######################################################################
######################################################################


#@ help                  - Usage information.
help() {
  egrep "^#@" $0 | cut --bytes=3-
}


#@ install-tests         - Download test tarball
install-tests() {
  mkdir -p ${TEST_ROOT}
  DownloadOrCopy ${TEST_TARBALL_URL} ${TEST_ROOT}/test_tarball.tgz
  tar jxf ${TEST_ROOT}/test_tarball.tgz -C ${TEST_ROOT}
}

#@
#@ clean                 - remove all tests
clean() {
  rm -rf  ${TEST_ROOT}
}

#@
#@ prereq-x8632
prereq-x8632() {
  # NOTE: we force the building of scons-out/nacl-x86-32/lib/crtX.o
  #       implicitly via run_intrinsics_test
  # this is only required for naclgcc_newlib tests
  ./scons platform=x86-32 irt_core sel_ldr run_intrinsics_test
}

#@
#@ prereq-x8664
prereq-x8664() {
  # NOTE: we force the building of scons-out/nacl-x86-64/lib/crtX.o
  #       implicitly via run_intrinsics_test
  # this is only required for naclgcc_newlib tests
  ./scons platform=x86-64 irt_core sel_ldr run_intrinsics_test
}

#@
#@ prereq-pnacl
prereq-pnacl() {
  tools/llvm/utman.sh sdk
}

#@
#@ prereq-arm
prereq-arm() {
  ./scons platform=arm irt_core sel_ldr run_intrinsics_test
}

standard_tests() {
  local config=$1
  local exclude=$2
  shift 2
  tools/toolchain_tester/toolchain_tester.py \
      --exclude=tools/toolchain_tester/${exclude} \
      --exclude=tools/toolchain_tester/known_failures_base.txt \
      --config=${config} \
      "$@" \
      ${TEST_PATH_C}/*c ${TEST_PATH_C}/ieee/*c
}

eh_tests() {
  local config=$1
  local exclude=$2
  shift 2
  tools/toolchain_tester/toolchain_tester.py \
      --config=${config} \
      --exclude=tools/toolchain_tester/unsuitable_dejagnu_tests.txt \
      --exclude=tools/toolchain_tester/${exclude} \
      "$@" \
      ${TEST_PATH_CPP}/eh/*.C
}

#@
#@ pnacl-x8632-torture
#@
pnacl-x8632-torture() {
  prereq-x8632
  prereq-pnacl
  eh_tests llvm_pnacl_x8632_O0 known_eh_failures_pnacl.txt "$@"
  eh_tests llvm_pnacl_x8632_O3 known_eh_failures_pnacl.txt "$@"
  standard_tests llvm_pnacl_x8632_O0 known_failures_pnacl.txt "$@"
  standard_tests llvm_pnacl_x8632_O3 known_failures_pnacl.txt "$@"
}

#@
#@ pnacl-x8664-torture
#@
pnacl-x8664-torture() {
  prereq-x8664
  prereq-pnacl
  eh_tests llvm_pnacl_x8664_O0 known_eh_failures_pnacl.txt "$@"
  eh_tests llvm_pnacl_x8664_O3 known_eh_failures_pnacl.txt "$@"
  standard_tests llvm_pnacl_x8664_O0 known_failures_pnacl.txt "$@"
  standard_tests llvm_pnacl_x8664_O3 known_failures_pnacl.txt "$@"
}

#@
#@ pnacl-arm-torture
#@
pnacl-arm-torture() {
  prereq-arm
  prereq-pnacl
  eh_tests llvm_pnacl_arm_O0 known_eh_failures_pnacl.txt "$@"
  eh_tests llvm_pnacl_arm_O3 known_eh_failures_pnacl.txt "$@"
  standard_tests llvm_pnacl_arm_O0 known_failures_pnacl.txt "$@"
  standard_tests llvm_pnacl_arm_O3 known_failures_pnacl.txt "$@"
}

#@
#@ naclgcc-x8632-torture
#@
naclgcc-x8632-torture() {
  prereq-x8632
  eh_tests nacl_gcc_x8632_O0 known_eh_failures_naclgcc.txt "$@"
  eh_tests nacl_gcc_x8632_O3 known_eh_failures_naclgcc.txt "$@"
  standard_tests nacl_gcc_x8632_O0 known_failures_naclgcc.txt "$@"
  standard_tests nacl_gcc_x8632_O3 known_failures_naclgcc.txt "$@"
}

#@
#@ naclgcc-x8664-torture
#@
naclgcc-x8664-torture() {
  prereq-x8664
  eh_tests nacl_gcc_x8664_O0 known_eh_failures_naclgcc.txt "$@"
  eh_tests nacl_gcc_x8664_O3 known_eh_failures_naclgcc.txt "$@"
  standard_tests nacl_gcc_x8664_O0 known_failures_naclgcc.txt "$@"
  standard_tests nacl_gcc_x8664_O3 known_failures_naclgcc.txt "$@"
}

#@
#@ localgcc-x8632-torture
#@
localgcc-x8632-torture() {
  eh_tests local_gcc_x8632_O0 known_eh_failures_localgcc.txt "$@"
  eh_tests local_gcc_x8632_O3 known_eh_failures_localgcc.txt "$@"
  standard_tests local_gcc_x8632_O0 known_failures_localgcc.txt "$@"
  standard_tests local_gcc_x8632_O3 known_failures_localgcc.txt "$@"
}

#@
#@ localgcc-x8664-torture
#@
localgcc-x8664-torture() {
  eh_tests local_gcc_x8664_O0 known_eh_failures_localgcc.txt "$@"
  eh_tests local_gcc_x8664_O3 known_eh_failures_localgcc.txt "$@"
  standard_tests local_gcc_x8664_O0 known_failures_localgcc.txt "$@"
  standard_tests local_gcc_x8664_O3 known_failures_localgcc.txt "$@"
}

#@
#@ trybot-pnacl-arm-torture
#@
trybot-pnacl-arm-torture() {
  install-tests
  pnacl-arm-torture
}

#@
#@ trybot-pnacl-x8632-torture
#@
trybot-pnacl-x8632-torture() {
  install-tests
  pnacl-x8632-torture
}

#@
#@ trybot-pnacl-x8664-torture
#@
trybot-pnacl-x8664-torture() {
  install-tests
  pnacl-x8664-torture
}

#@
#@ trybot-pnacl-x8632-torture
#@
trybot-naclgcc-x8632-torture() {
  install-tests
  naclgcc-x8632-torture
}

#@
#@ trybot-pnacl-x8664-torture
#@
trybot-naclgcc-x8664-torture() {
  install-tests
  naclgcc-x8664-torture
}

######################################################################
######################################################################
#
#                               < MAIN >
#
######################################################################
######################################################################

if [ $# = 0 ]; then set -- help; fi  # Avoid reference to undefined $1.

if [ "$(type -t $1)" != "function" ]; then
  #Usage
  echo "ERROR: unknown function '$1'." >&2
  echo "For help, try:"
  echo "    $0 help"
  exit 1
fi

"$@"