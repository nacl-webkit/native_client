/*
 * Copyright 2008 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can
 * be found in the LICENSE file.
 */

/*
 * NaCl Secure Runtime
 */

#include "native_client/src/trusted/desc/nacl_desc_effector_ldr.h"


uint16_t  nacl_global_cs = 0;
uint16_t  nacl_global_ds = 0;


void NaClInitGlobals() {
  nacl_global_cs = NaClGetCs();
  nacl_global_ds = NaClGetDs();
}

uint16_t NaClGetGlobalDs() {
  return nacl_global_ds;
}

uint16_t NaClGetGlobalCs() {
  return nacl_global_cs;
}

int NaClThreadContextCtor(struct NaClThreadContext  *ntcp,
                          struct NaClApp            *nap,
                          uintptr_t                 prog_ctr,
                          uintptr_t                 stack_ptr,
                          uint32_t                  tls_idx) {
  NaClLog(4, "&nap->code_seg_sel = 0x%08"PRIxPTR"\n",
          (uintptr_t) &nap->code_seg_sel);
  NaClLog(4, "&nap->data_seg_sel = 0x%08"PRIxPTR"\n",
          (uintptr_t) &nap->data_seg_sel);
  NaClLog(4, "nap->code_seg_sel = 0x%02x\n", nap->code_seg_sel);
  NaClLog(4, "nap->data_seg_sel = 0x%02x\n", nap->data_seg_sel);

  /*
   * initialize registers to appropriate values.  most registers just
   * get zero, but for the segment register we allocate segment
   * selectors for the NaCl app, based on its address space.
   */
  ntcp->ebx = 0;
  ntcp->esi = 0;
  ntcp->edi = 0;
#if NACL_BUILD_SUBARCH == 64
  ntcp->frame_ptr.ptr_64 = 0;
  ntcp->stack_ptr.ptr_64 = stack_ptr;
#else
  ntcp->frame_ptr.ptr_32.ptr = 0;
  ntcp->stack_ptr.ptr_32.ptr = stack_ptr;
#endif
  ntcp->prog_ctr = prog_ctr;

  ntcp->cs = nap->code_seg_sel;
  ntcp->ds = nap->data_seg_sel;

  ntcp->es = nap->data_seg_sel;
  ntcp->fs = 0;  /* windows use this for TLS and SEH; linux does not */
  ntcp->gs = (uint16_t)tls_idx;
  ntcp->ss = nap->data_seg_sel;

  NaClLog(4, "user.cs: 0x%02x\n", ntcp->cs);
  NaClLog(4, "user.fs: 0x%02x\n", ntcp->fs);
  NaClLog(4, "user.gs: 0x%02x\n", ntcp->gs);
  NaClLog(4, "user.ss: 0x%02x\n", ntcp->ss);

  return 1;
}
