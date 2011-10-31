#!/bin/bash

# This is a temporary hack to see whether we can build libstdc++ from
# gcc 4.6.1 with pnacl-clang
#  Upon success this should be folded into utman
# NOTE: run this in native_client/ like so
#
# pnacl/unsupported/build-libstdc++.sh download
# pnacl/unsupported/build-libstdc++.sh libstdcpp-patch
# pnacl/unsupported/build-libstdc++.sh libstdcpp-configure
# pnacl/unsupported/build-libstdc++.sh libstdcpp-make -k
#
set -o nounset
set -o errexit


readonly INSTALL_ROOT="$(pwd)/toolchain/pnacl_linux_x86_64_newlib"
readonly INSTALL_BIN="${INSTALL_ROOT}/bin"
readonly INSTALL_LIB="${INSTALL_ROOT}/lib"
readonly LIBSTDCPP_INSTALL_DIR="${INSTALL_ROOT}/pkg/libstdcpp"
readonly BUILD=cpp-build
readonly GCC_SRC="$(pwd)/pnacl/git/gcc"

CC=gcc


# Location of PNaCl gcc/g++/as
readonly PNACL_GCC="${INSTALL_BIN}/pnacl-gcc"
readonly PNACL_GXX="${INSTALL_BIN}/pnacl-g++"
readonly PNACL_CLANG="${INSTALL_BIN}/pnacl-clang"
readonly PNACL_CLANGXX="${INSTALL_BIN}/pnacl-clang++"
readonly PNACL_AR="${INSTALL_BIN}/pnacl-ar"
readonly PNACL_RANLIB="${INSTALL_BIN}/pnacl-ranlib"
readonly PNACL_AS="${INSTALL_BIN}/pnacl-as"
readonly PNACL_LD="${INSTALL_BIN}/pnacl-ld"
readonly PNACL_NM="${INSTALL_BIN}/pnacl-nm"
readonly PNACL_TRANSLATE="${INSTALL_BIN}/pnacl-translate"
readonly PNACL_READELF="${INSTALL_BIN}/readelf"
readonly PNACL_SIZE="${INSTALL_BIN}/size"
readonly PNACL_STRIP="${INSTALL_BIN}/pnacl-strip"

readonly PNACL_AS_ARM="${INSTALL_BIN}/pnacl-arm-as"
readonly PNACL_AS_X8632="${INSTALL_BIN}/pnacl-i686-as"
readonly PNACL_AS_X8664="${INSTALL_BIN}/pnacl-x86_64-as"


readonly ILLEGAL_TOOL=${INSTALL_BIN}/pnacl-illegal

STD_ENV_FOR_LIBSTDCPP_CLANG=(
  CC_FOR_BUILD="${CC}"
  CC="${PNACL_CLANG}"
  CXX="${PNACL_CLANGXX}"
  RAW_CXX_FOR_TARGET="${PNACL_CLANGXX}"
  LD="${ILLEGAL_TOOL}"
  CFLAGS="--pnacl-arm-bias"
  CPPFLAGS="--pnacl-arm-bias"
  CXXFLAGS="--pnacl-arm-bias "
  CFLAGS_FOR_TARGET="--pnacl-arm-bias"
  CPPFLAGS_FOR_TARGET="--pnacl-arm-bias"
  CC_FOR_TARGET="${PNACL_CLANG}"
  GCC_FOR_TARGET="${PNACL_CLANG}"
  CXX_FOR_TARGET="${PNACL_CLANGXX}"
  AR="${PNACL_AR}"
  AR_FOR_TARGET="${PNACL_AR}"
  NM_FOR_TARGET="${PNACL_NM}"
  RANLIB="${PNACL_RANLIB}"
  RANLIB_FOR_TARGET="${PNACL_RANLIB}"
  AS_FOR_TARGET="${ILLEGAL_TOOL}"
  LD_FOR_TARGET="${ILLEGAL_TOOL}"
  OBJDUMP_FOR_TARGET="${ILLEGAL_TOOL}" )


unpatch() {
  pushd ${GCC_SRC}
  git reset --hard HEAD
  popd
}

generate-patch() {
  pushd ${GCC_SRC}
  git diff
  popd
}

libstdcpp-patch() {
  pushd ${GCC_SRC}
  patch -p1 < ../../../pnacl/unsupported/patch-libstdc++
  popd
}


libstdcpp-configure() {
  mkdir -p ${BUILD}
  pushd ${BUILD}

  env -i PATH=/usr/bin/:/bin  "${STD_ENV_FOR_LIBSTDCPP_CLANG[@]}" \
    ${GCC_SRC}/libstdc++-v3/configure \
    --host=arm-none-linux-gnueabi \
    --disable-shared \
    --disable-rpath \
    --enable-shared=no \
    --disable-libstdcxx-pch \
    --enable-linux-futex=no \
    --with-newlib \
    --enable-cxx-flags="-D__SIZE_MAX__=4294967295"\
    --enable-libstdcxx-time=no \
    --enable-sjlj-exceptions=no \
    --prefix="${LIBSTDCPP_INSTALL_DIR}" \
    --enable-multilib=no \
    "$@"
  popd
}


libstdcpp-make() {
  pushd  ${BUILD}
  env -i PATH=/usr/bin/:/bin "${STD_ENV_FOR_LIBSTDCPP_CLANG[@]}" \
        make \
        "$@"
  popd
}


libstdcpp-install() {
  pushd  ${BUILD}
  # install headers (=install-data)
  # for good measure make sure we do not keep any old headers
  rm -rf "${INSTALL_ROOT}/include/c++"
  rm -rf "${LIBSTDCPP_INSTALL_DIR}"
  env -i PATH=/usr/bin/:/bin "${STD_ENV_FOR_LIBSTDCPP_CLANG[@]}" \
    make \
    install-data \
    "$@"

  # Install bitcode library
  mkdir -p "${INSTALL_LIB}"
  cp src/.libs/libstdc++.a "${INSTALL_LIB}"

  popd
}

all() {
  unpatch
  libstdcpp-patch
  libstdcpp-configure
  libstdcpp-make
  libstdcpp-install
}

"$@"