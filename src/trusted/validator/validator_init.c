/*
 * Copyright (c) 2012 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <assert.h>
#include "native_client/src/shared/platform/nacl_log.h"
#include "native_client/src/trusted/validator/ncvalidate.h"


/* The function is not static to avoid compiler error on platforms where it is
 * not used.
 */
void EmitExperimentalValidatorWarning(void) {
  NaClLog(LOG_WARNING, "DANGER! USING THE EXPERIMENTAL DFA VALIDATOR!\n");
}

const struct NaClValidatorInterface *NaClCreateValidator(void) {
//FIXME #if NACL_ARCH(NACL_BUILD_ARCH) == NACL_arm
//FIXME   return NaClValidatorCreateArm();
//FIXME #elif NACL_ARCH(NACL_BUILD_ARCH) == NACL_mips
//FIXME   return NaClValidatorCreateMips();
//FIXME #elif NACL_ARCH(NACL_TARGET_ARCH) == NACL_x86
//FIXME # if NACL_TARGET_SUBARCH == 64
//FIXME #  if defined(NACL_VALIDATOR_RAGEL)
//FIXME   EmitExperimentalValidatorWarning();
//FIXME   return NaClDfaValidatorCreate_x86_64();
//FIXME #  else
  return NaClValidatorCreate_x86_64();
//FIXME #  endif  /* defined(NACL_VALIDATOR_RAGEL) */
//FIXME # elif NACL_TARGET_SUBARCH == 32
//FIXME #  if defined(NACL_VALIDATOR_RAGEL)
//FIXME   EmitExperimentalValidatorWarning();
//FIXME   return NaClDfaValidatorCreate_x86_32();
//FIXME #  else
//FIXME   return NaClValidatorCreate_x86_32();
//FIXME #  endif  /* defined(NACL_VALIDATOR_RAGEL) */
//FIXME # else
//FIXME #  error "Invalid sub-architecture!"
//FIXME # endif
//FIXME #else  /* NACL_x86 */
//FIXME # error "There is no validator for this architecture!"
//FIXME #endif
}
