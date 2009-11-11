/*
 * Copyright 2008  The Native Client Authors.  All rights reserved.
 * Use of this source code is governed by a BSD-style license that can
 * be found in the LICENSE file.
 */

/*
 * Gather ye all module initializations and finalizations needed by
 * the NRD transfer protocol code here.
 */

#include "native_client/src/trusted/desc/nrd_all_modules.h"
#include "native_client/src/shared/platform/nacl_global_secure_random.h"
#include "native_client/src/shared/platform/nacl_log.h"
#include "native_client/src/shared/platform/nacl_secure_random.h"
#include "native_client/src/shared/platform/nacl_time.h"

void NaClNrdAllModulesInit(void) {
  /*
   * NaClLogModuleInit examines NACLLOG and NACLVERBOSITY environment
   * variables.
   */
  NaClLogModuleInit();
  NaClSecureRngModuleInit();
  NaClGlobalSecureRngInit();
  NaClTimeInit();
}

void NaClNrdAllModulesFini(void) {
  NaClTimeFini();
  NaClGlobalSecureRngFini();
  NaClSecureRngModuleFini();
  NaClLogModuleFini();
}
