/*
 * Copyright 2012 The Native Client Authors.  All rights reserved.
 * Use of this source code is governed by a BSD-style license that can
 * be found in the LICENSE file.
 */

// DO NOT EDIT: GENERATED CODE

#ifndef NACL_TRUSTED_BUT_NOT_TCB
#error This file is not meant for use in the TCB
#endif


#include "gtest/gtest.h"
#include "native_client/src/trusted/validator_arm/actual_vs_baseline.h"
#include "native_client/src/trusted/validator_arm/actual_classes.h"
#include "native_client/src/trusted/validator_arm/baseline_classes.h"
#include "native_client/src/trusted/validator_arm/inst_classes_testers.h"

namespace nacl_arm_test {

// The following classes are derived class decoder testers that
// add row pattern constraints and decoder restrictions to each tester.
// This is done so that it can be used to make sure that the
// corresponding pattern is not tested for cases that would be excluded
//  due to row checks, or restrictions specified by the row restrictions.


// Neutral case:
// inst(19:16)=0000 & inst(7:6)=01
//    = CondVfpOp {'constraints': }
//
// Representaive case:
// opc2(19:16)=0000 & opc3(7:6)=01
//    = CondVfpOp {constraints: }
class CondVfpOpTesterCase0
    : public CondVfpOpTester {
 public:
  CondVfpOpTesterCase0(const NamedClassDecoder& decoder)
    : CondVfpOpTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
};

bool CondVfpOpTesterCase0
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  if ((inst.Bits() & 0x000F0000) != 0x00000000 /* opc2(19:16)=~0000 */) return false;
  if ((inst.Bits() & 0x000000C0) != 0x00000040 /* opc3(7:6)=~01 */) return false;

  // Check other preconditions defined for the base decoder.
  return CondVfpOpTester::
      PassesParsePreconditions(inst, decoder);
}

// Neutral case:
// inst(19:16)=0000 & inst(7:6)=11
//    = CondVfpOp {'constraints': }
//
// Representaive case:
// opc2(19:16)=0000 & opc3(7:6)=11
//    = CondVfpOp {constraints: }
class CondVfpOpTesterCase1
    : public CondVfpOpTester {
 public:
  CondVfpOpTesterCase1(const NamedClassDecoder& decoder)
    : CondVfpOpTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
};

bool CondVfpOpTesterCase1
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  if ((inst.Bits() & 0x000F0000) != 0x00000000 /* opc2(19:16)=~0000 */) return false;
  if ((inst.Bits() & 0x000000C0) != 0x000000C0 /* opc3(7:6)=~11 */) return false;

  // Check other preconditions defined for the base decoder.
  return CondVfpOpTester::
      PassesParsePreconditions(inst, decoder);
}

// Neutral case:
// inst(19:16)=0001 & inst(7:6)=01
//    = CondVfpOp {'constraints': }
//
// Representaive case:
// opc2(19:16)=0001 & opc3(7:6)=01
//    = CondVfpOp {constraints: }
class CondVfpOpTesterCase2
    : public CondVfpOpTester {
 public:
  CondVfpOpTesterCase2(const NamedClassDecoder& decoder)
    : CondVfpOpTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
};

bool CondVfpOpTesterCase2
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  if ((inst.Bits() & 0x000F0000) != 0x00010000 /* opc2(19:16)=~0001 */) return false;
  if ((inst.Bits() & 0x000000C0) != 0x00000040 /* opc3(7:6)=~01 */) return false;

  // Check other preconditions defined for the base decoder.
  return CondVfpOpTester::
      PassesParsePreconditions(inst, decoder);
}

// Neutral case:
// inst(19:16)=0001 & inst(7:6)=11
//    = CondVfpOp {'constraints': }
//
// Representaive case:
// opc2(19:16)=0001 & opc3(7:6)=11
//    = CondVfpOp {constraints: }
class CondVfpOpTesterCase3
    : public CondVfpOpTester {
 public:
  CondVfpOpTesterCase3(const NamedClassDecoder& decoder)
    : CondVfpOpTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
};

bool CondVfpOpTesterCase3
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  if ((inst.Bits() & 0x000F0000) != 0x00010000 /* opc2(19:16)=~0001 */) return false;
  if ((inst.Bits() & 0x000000C0) != 0x000000C0 /* opc3(7:6)=~11 */) return false;

  // Check other preconditions defined for the base decoder.
  return CondVfpOpTester::
      PassesParsePreconditions(inst, decoder);
}

// Neutral case:
// inst(19:16)=0100 & inst(7:6)=x1
//    = CondVfpOp {'constraints': }
//
// Representaive case:
// opc2(19:16)=0100 & opc3(7:6)=x1
//    = CondVfpOp {constraints: }
class CondVfpOpTesterCase4
    : public CondVfpOpTester {
 public:
  CondVfpOpTesterCase4(const NamedClassDecoder& decoder)
    : CondVfpOpTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
};

bool CondVfpOpTesterCase4
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  if ((inst.Bits() & 0x000F0000) != 0x00040000 /* opc2(19:16)=~0100 */) return false;
  if ((inst.Bits() & 0x00000040) != 0x00000040 /* opc3(7:6)=~x1 */) return false;

  // Check other preconditions defined for the base decoder.
  return CondVfpOpTester::
      PassesParsePreconditions(inst, decoder);
}

// Neutral case:
// inst(19:16)=0101 & inst(7:6)=x1 & inst(31:0)=xxxxxxxxxxxxxxxxxxxxxxxxxx0x0000
//    = CondVfpOp {'constraints': }
//
// Representaive case:
// opc2(19:16)=0101 & opc3(7:6)=x1 & $pattern(31:0)=xxxxxxxxxxxxxxxxxxxxxxxxxx0x0000
//    = CondVfpOp {constraints: }
class CondVfpOpTesterCase5
    : public CondVfpOpTester {
 public:
  CondVfpOpTesterCase5(const NamedClassDecoder& decoder)
    : CondVfpOpTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
};

bool CondVfpOpTesterCase5
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  if ((inst.Bits() & 0x000F0000) != 0x00050000 /* opc2(19:16)=~0101 */) return false;
  if ((inst.Bits() & 0x00000040) != 0x00000040 /* opc3(7:6)=~x1 */) return false;
  if ((inst.Bits() & 0x0000002F) != 0x00000000 /* $pattern(31:0)=~xxxxxxxxxxxxxxxxxxxxxxxxxx0x0000 */) return false;

  // Check other preconditions defined for the base decoder.
  return CondVfpOpTester::
      PassesParsePreconditions(inst, decoder);
}

// Neutral case:
// inst(19:16)=0111 & inst(7:6)=11
//    = CondVfpOp {'constraints': }
//
// Representaive case:
// opc2(19:16)=0111 & opc3(7:6)=11
//    = CondVfpOp {constraints: }
class CondVfpOpTesterCase6
    : public CondVfpOpTester {
 public:
  CondVfpOpTesterCase6(const NamedClassDecoder& decoder)
    : CondVfpOpTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
};

bool CondVfpOpTesterCase6
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  if ((inst.Bits() & 0x000F0000) != 0x00070000 /* opc2(19:16)=~0111 */) return false;
  if ((inst.Bits() & 0x000000C0) != 0x000000C0 /* opc3(7:6)=~11 */) return false;

  // Check other preconditions defined for the base decoder.
  return CondVfpOpTester::
      PassesParsePreconditions(inst, decoder);
}

// Neutral case:
// inst(19:16)=1000 & inst(7:6)=x1
//    = CondVfpOp {'constraints': }
//
// Representaive case:
// opc2(19:16)=1000 & opc3(7:6)=x1
//    = CondVfpOp {constraints: }
class CondVfpOpTesterCase7
    : public CondVfpOpTester {
 public:
  CondVfpOpTesterCase7(const NamedClassDecoder& decoder)
    : CondVfpOpTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
};

bool CondVfpOpTesterCase7
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  if ((inst.Bits() & 0x000F0000) != 0x00080000 /* opc2(19:16)=~1000 */) return false;
  if ((inst.Bits() & 0x00000040) != 0x00000040 /* opc3(7:6)=~x1 */) return false;

  // Check other preconditions defined for the base decoder.
  return CondVfpOpTester::
      PassesParsePreconditions(inst, decoder);
}

// Neutral case:
// inst(19:16)=001x & inst(7:6)=x1 & inst(31:0)=xxxxxxxxxxxxxxxxxxxxxxx0xxxxxxxx
//    = CondVfpOp {'constraints': }
//
// Representaive case:
// opc2(19:16)=001x & opc3(7:6)=x1 & $pattern(31:0)=xxxxxxxxxxxxxxxxxxxxxxx0xxxxxxxx
//    = CondVfpOp {constraints: }
class CondVfpOpTesterCase8
    : public CondVfpOpTester {
 public:
  CondVfpOpTesterCase8(const NamedClassDecoder& decoder)
    : CondVfpOpTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
};

bool CondVfpOpTesterCase8
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  if ((inst.Bits() & 0x000E0000) != 0x00020000 /* opc2(19:16)=~001x */) return false;
  if ((inst.Bits() & 0x00000040) != 0x00000040 /* opc3(7:6)=~x1 */) return false;
  if ((inst.Bits() & 0x00000100) != 0x00000000 /* $pattern(31:0)=~xxxxxxxxxxxxxxxxxxxxxxx0xxxxxxxx */) return false;

  // Check other preconditions defined for the base decoder.
  return CondVfpOpTester::
      PassesParsePreconditions(inst, decoder);
}

// Neutral case:
// inst(19:16)=101x & inst(7:6)=x1
//    = CondVfpOp {'constraints': }
//
// Representaive case:
// opc2(19:16)=101x & opc3(7:6)=x1
//    = CondVfpOp {constraints: }
class CondVfpOpTesterCase9
    : public CondVfpOpTester {
 public:
  CondVfpOpTesterCase9(const NamedClassDecoder& decoder)
    : CondVfpOpTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
};

bool CondVfpOpTesterCase9
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  if ((inst.Bits() & 0x000E0000) != 0x000A0000 /* opc2(19:16)=~101x */) return false;
  if ((inst.Bits() & 0x00000040) != 0x00000040 /* opc3(7:6)=~x1 */) return false;

  // Check other preconditions defined for the base decoder.
  return CondVfpOpTester::
      PassesParsePreconditions(inst, decoder);
}

// Neutral case:
// inst(19:16)=110x & inst(7:6)=x1
//    = CondVfpOp {'constraints': }
//
// Representaive case:
// opc2(19:16)=110x & opc3(7:6)=x1
//    = CondVfpOp {constraints: }
class CondVfpOpTesterCase10
    : public CondVfpOpTester {
 public:
  CondVfpOpTesterCase10(const NamedClassDecoder& decoder)
    : CondVfpOpTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
};

bool CondVfpOpTesterCase10
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  if ((inst.Bits() & 0x000E0000) != 0x000C0000 /* opc2(19:16)=~110x */) return false;
  if ((inst.Bits() & 0x00000040) != 0x00000040 /* opc3(7:6)=~x1 */) return false;

  // Check other preconditions defined for the base decoder.
  return CondVfpOpTester::
      PassesParsePreconditions(inst, decoder);
}

// Neutral case:
// inst(19:16)=111x & inst(7:6)=x1
//    = CondVfpOp {'constraints': }
//
// Representaive case:
// opc2(19:16)=111x & opc3(7:6)=x1
//    = CondVfpOp {constraints: }
class CondVfpOpTesterCase11
    : public CondVfpOpTester {
 public:
  CondVfpOpTesterCase11(const NamedClassDecoder& decoder)
    : CondVfpOpTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
};

bool CondVfpOpTesterCase11
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  if ((inst.Bits() & 0x000E0000) != 0x000E0000 /* opc2(19:16)=~111x */) return false;
  if ((inst.Bits() & 0x00000040) != 0x00000040 /* opc3(7:6)=~x1 */) return false;

  // Check other preconditions defined for the base decoder.
  return CondVfpOpTester::
      PassesParsePreconditions(inst, decoder);
}

// Neutral case:
// inst(23:20)=0x00
//    = CondVfpOp {'constraints': }
//
// Representaive case:
// opc1(23:20)=0x00
//    = CondVfpOp {constraints: }
class CondVfpOpTesterCase12
    : public CondVfpOpTester {
 public:
  CondVfpOpTesterCase12(const NamedClassDecoder& decoder)
    : CondVfpOpTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
};

bool CondVfpOpTesterCase12
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  if ((inst.Bits() & 0x00B00000) != 0x00000000 /* opc1(23:20)=~0x00 */) return false;

  // Check other preconditions defined for the base decoder.
  return CondVfpOpTester::
      PassesParsePreconditions(inst, decoder);
}

// Neutral case:
// inst(23:20)=0x01
//    = CondVfpOp {'constraints': }
//
// Representaive case:
// opc1(23:20)=0x01
//    = CondVfpOp {constraints: }
class CondVfpOpTesterCase13
    : public CondVfpOpTester {
 public:
  CondVfpOpTesterCase13(const NamedClassDecoder& decoder)
    : CondVfpOpTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
};

bool CondVfpOpTesterCase13
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  if ((inst.Bits() & 0x00B00000) != 0x00100000 /* opc1(23:20)=~0x01 */) return false;

  // Check other preconditions defined for the base decoder.
  return CondVfpOpTester::
      PassesParsePreconditions(inst, decoder);
}

// Neutral case:
// inst(23:20)=0x10 & inst(7:6)=x0
//    = CondVfpOp {'constraints': }
//
// Representaive case:
// opc1(23:20)=0x10 & opc3(7:6)=x0
//    = CondVfpOp {constraints: }
class CondVfpOpTesterCase14
    : public CondVfpOpTester {
 public:
  CondVfpOpTesterCase14(const NamedClassDecoder& decoder)
    : CondVfpOpTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
};

bool CondVfpOpTesterCase14
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  if ((inst.Bits() & 0x00B00000) != 0x00200000 /* opc1(23:20)=~0x10 */) return false;
  if ((inst.Bits() & 0x00000040) != 0x00000000 /* opc3(7:6)=~x0 */) return false;

  // Check other preconditions defined for the base decoder.
  return CondVfpOpTester::
      PassesParsePreconditions(inst, decoder);
}

// Neutral case:
// inst(23:20)=0x10 & inst(7:6)=x1
//    = CondVfpOp {'constraints': }
//
// Representaive case:
// opc1(23:20)=0x10 & opc3(7:6)=x1
//    = CondVfpOp {constraints: }
class CondVfpOpTesterCase15
    : public CondVfpOpTester {
 public:
  CondVfpOpTesterCase15(const NamedClassDecoder& decoder)
    : CondVfpOpTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
};

bool CondVfpOpTesterCase15
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  if ((inst.Bits() & 0x00B00000) != 0x00200000 /* opc1(23:20)=~0x10 */) return false;
  if ((inst.Bits() & 0x00000040) != 0x00000040 /* opc3(7:6)=~x1 */) return false;

  // Check other preconditions defined for the base decoder.
  return CondVfpOpTester::
      PassesParsePreconditions(inst, decoder);
}

// Neutral case:
// inst(23:20)=0x11 & inst(7:6)=x0
//    = CondVfpOp {'constraints': }
//
// Representaive case:
// opc1(23:20)=0x11 & opc3(7:6)=x0
//    = CondVfpOp {constraints: }
class CondVfpOpTesterCase16
    : public CondVfpOpTester {
 public:
  CondVfpOpTesterCase16(const NamedClassDecoder& decoder)
    : CondVfpOpTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
};

bool CondVfpOpTesterCase16
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  if ((inst.Bits() & 0x00B00000) != 0x00300000 /* opc1(23:20)=~0x11 */) return false;
  if ((inst.Bits() & 0x00000040) != 0x00000000 /* opc3(7:6)=~x0 */) return false;

  // Check other preconditions defined for the base decoder.
  return CondVfpOpTester::
      PassesParsePreconditions(inst, decoder);
}

// Neutral case:
// inst(23:20)=0x11 & inst(7:6)=x1
//    = CondVfpOp {'constraints': }
//
// Representaive case:
// opc1(23:20)=0x11 & opc3(7:6)=x1
//    = CondVfpOp {constraints: }
class CondVfpOpTesterCase17
    : public CondVfpOpTester {
 public:
  CondVfpOpTesterCase17(const NamedClassDecoder& decoder)
    : CondVfpOpTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
};

bool CondVfpOpTesterCase17
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  if ((inst.Bits() & 0x00B00000) != 0x00300000 /* opc1(23:20)=~0x11 */) return false;
  if ((inst.Bits() & 0x00000040) != 0x00000040 /* opc3(7:6)=~x1 */) return false;

  // Check other preconditions defined for the base decoder.
  return CondVfpOpTester::
      PassesParsePreconditions(inst, decoder);
}

// Neutral case:
// inst(23:20)=1x00 & inst(7:6)=x0
//    = CondVfpOp {'constraints': }
//
// Representaive case:
// opc1(23:20)=1x00 & opc3(7:6)=x0
//    = CondVfpOp {constraints: }
class CondVfpOpTesterCase18
    : public CondVfpOpTester {
 public:
  CondVfpOpTesterCase18(const NamedClassDecoder& decoder)
    : CondVfpOpTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
};

bool CondVfpOpTesterCase18
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  if ((inst.Bits() & 0x00B00000) != 0x00800000 /* opc1(23:20)=~1x00 */) return false;
  if ((inst.Bits() & 0x00000040) != 0x00000000 /* opc3(7:6)=~x0 */) return false;

  // Check other preconditions defined for the base decoder.
  return CondVfpOpTester::
      PassesParsePreconditions(inst, decoder);
}

// Neutral case:
// inst(23:20)=1x01
//    = CondVfpOp {'constraints': }
//
// Representaive case:
// opc1(23:20)=1x01
//    = CondVfpOp {constraints: }
class CondVfpOpTesterCase19
    : public CondVfpOpTester {
 public:
  CondVfpOpTesterCase19(const NamedClassDecoder& decoder)
    : CondVfpOpTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
};

bool CondVfpOpTesterCase19
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  if ((inst.Bits() & 0x00B00000) != 0x00900000 /* opc1(23:20)=~1x01 */) return false;

  // Check other preconditions defined for the base decoder.
  return CondVfpOpTester::
      PassesParsePreconditions(inst, decoder);
}

// Neutral case:
// inst(23:20)=1x10
//    = CondVfpOp {'constraints': }
//
// Representaive case:
// opc1(23:20)=1x10
//    = CondVfpOp {constraints: }
class CondVfpOpTesterCase20
    : public CondVfpOpTester {
 public:
  CondVfpOpTesterCase20(const NamedClassDecoder& decoder)
    : CondVfpOpTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
};

bool CondVfpOpTesterCase20
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  if ((inst.Bits() & 0x00B00000) != 0x00A00000 /* opc1(23:20)=~1x10 */) return false;

  // Check other preconditions defined for the base decoder.
  return CondVfpOpTester::
      PassesParsePreconditions(inst, decoder);
}

// Neutral case:
// inst(7:6)=x0 & inst(31:0)=xxxxxxxxxxxxxxxxxxxxxxxx0x0xxxxx
//    = CondVfpOp {'constraints': }
//
// Representaive case:
// opc3(7:6)=x0 & $pattern(31:0)=xxxxxxxxxxxxxxxxxxxxxxxx0x0xxxxx
//    = CondVfpOp {constraints: }
class CondVfpOpTesterCase21
    : public CondVfpOpTester {
 public:
  CondVfpOpTesterCase21(const NamedClassDecoder& decoder)
    : CondVfpOpTester(decoder) {}
  virtual bool PassesParsePreconditions(
      nacl_arm_dec::Instruction inst,
      const NamedClassDecoder& decoder);
};

bool CondVfpOpTesterCase21
::PassesParsePreconditions(
     nacl_arm_dec::Instruction inst,
     const NamedClassDecoder& decoder) {

  // Check that row patterns apply to pattern being checked.'
  if ((inst.Bits() & 0x00000040) != 0x00000000 /* opc3(7:6)=~x0 */) return false;
  if ((inst.Bits() & 0x000000A0) != 0x00000000 /* $pattern(31:0)=~xxxxxxxxxxxxxxxxxxxxxxxx0x0xxxxx */) return false;

  // Check other preconditions defined for the base decoder.
  return CondVfpOpTester::
      PassesParsePreconditions(inst, decoder);
}

// The following are derived class decoder testers for decoder actions
// associated with a pattern of an action. These derived classes introduce
// a default constructor that automatically initializes the expected decoder
// to the corresponding instance in the generated DecoderState.

// Neutral case:
// inst(19:16)=0000 & inst(7:6)=01
//    = CondVfpOp {'constraints': ,
//     'rule': 'Vmov_Rule_327_A2_P642'}
//
// Representative case:
// opc2(19:16)=0000 & opc3(7:6)=01
//    = CondVfpOp {constraints: ,
//     rule: Vmov_Rule_327_A2_P642}
class CondVfpOpTester_Case0
    : public CondVfpOpTesterCase0 {
 public:
  CondVfpOpTester_Case0()
    : CondVfpOpTesterCase0(
      state_.CondVfpOp_Vmov_Rule_327_A2_P642_instance_)
  {}
};

// Neutral case:
// inst(19:16)=0000 & inst(7:6)=11
//    = CondVfpOp {'constraints': ,
//     'rule': 'Vabs_Rule_269_A2_P532'}
//
// Representative case:
// opc2(19:16)=0000 & opc3(7:6)=11
//    = CondVfpOp {constraints: ,
//     rule: Vabs_Rule_269_A2_P532}
class CondVfpOpTester_Case1
    : public CondVfpOpTesterCase1 {
 public:
  CondVfpOpTester_Case1()
    : CondVfpOpTesterCase1(
      state_.CondVfpOp_Vabs_Rule_269_A2_P532_instance_)
  {}
};

// Neutral case:
// inst(19:16)=0001 & inst(7:6)=01
//    = CondVfpOp {'constraints': ,
//     'rule': 'Vneg_Rule_342_A2_P672'}
//
// Representative case:
// opc2(19:16)=0001 & opc3(7:6)=01
//    = CondVfpOp {constraints: ,
//     rule: Vneg_Rule_342_A2_P672}
class CondVfpOpTester_Case2
    : public CondVfpOpTesterCase2 {
 public:
  CondVfpOpTester_Case2()
    : CondVfpOpTesterCase2(
      state_.CondVfpOp_Vneg_Rule_342_A2_P672_instance_)
  {}
};

// Neutral case:
// inst(19:16)=0001 & inst(7:6)=11
//    = CondVfpOp {'constraints': ,
//     'rule': 'Vsqrt_Rule_388_A1_P762'}
//
// Representative case:
// opc2(19:16)=0001 & opc3(7:6)=11
//    = CondVfpOp {constraints: ,
//     rule: Vsqrt_Rule_388_A1_P762}
class CondVfpOpTester_Case3
    : public CondVfpOpTesterCase3 {
 public:
  CondVfpOpTester_Case3()
    : CondVfpOpTesterCase3(
      state_.CondVfpOp_Vsqrt_Rule_388_A1_P762_instance_)
  {}
};

// Neutral case:
// inst(19:16)=0100 & inst(7:6)=x1
//    = CondVfpOp {'constraints': ,
//     'rule': 'Vcmp_Vcmpe_Rule_A1'}
//
// Representative case:
// opc2(19:16)=0100 & opc3(7:6)=x1
//    = CondVfpOp {constraints: ,
//     rule: Vcmp_Vcmpe_Rule_A1}
class CondVfpOpTester_Case4
    : public CondVfpOpTesterCase4 {
 public:
  CondVfpOpTester_Case4()
    : CondVfpOpTesterCase4(
      state_.CondVfpOp_Vcmp_Vcmpe_Rule_A1_instance_)
  {}
};

// Neutral case:
// inst(19:16)=0101 & inst(7:6)=x1 & inst(31:0)=xxxxxxxxxxxxxxxxxxxxxxxxxx0x0000
//    = CondVfpOp {'constraints': ,
//     'rule': 'Vcmp_Vcmpe_Rule_A2'}
//
// Representative case:
// opc2(19:16)=0101 & opc3(7:6)=x1 & $pattern(31:0)=xxxxxxxxxxxxxxxxxxxxxxxxxx0x0000
//    = CondVfpOp {constraints: ,
//     rule: Vcmp_Vcmpe_Rule_A2}
class CondVfpOpTester_Case5
    : public CondVfpOpTesterCase5 {
 public:
  CondVfpOpTester_Case5()
    : CondVfpOpTesterCase5(
      state_.CondVfpOp_Vcmp_Vcmpe_Rule_A2_instance_)
  {}
};

// Neutral case:
// inst(19:16)=0111 & inst(7:6)=11
//    = CondVfpOp {'constraints': ,
//     'rule': 'Vcvt_Rule_298_A1_P584'}
//
// Representative case:
// opc2(19:16)=0111 & opc3(7:6)=11
//    = CondVfpOp {constraints: ,
//     rule: Vcvt_Rule_298_A1_P584}
class CondVfpOpTester_Case6
    : public CondVfpOpTesterCase6 {
 public:
  CondVfpOpTester_Case6()
    : CondVfpOpTesterCase6(
      state_.CondVfpOp_Vcvt_Rule_298_A1_P584_instance_)
  {}
};

// Neutral case:
// inst(19:16)=1000 & inst(7:6)=x1
//    = CondVfpOp {'constraints': ,
//     'rule': 'Vcvt_Vcvtr_Rule_295_A1_P578'}
//
// Representative case:
// opc2(19:16)=1000 & opc3(7:6)=x1
//    = CondVfpOp {constraints: ,
//     rule: Vcvt_Vcvtr_Rule_295_A1_P578}
class CondVfpOpTester_Case7
    : public CondVfpOpTesterCase7 {
 public:
  CondVfpOpTester_Case7()
    : CondVfpOpTesterCase7(
      state_.CondVfpOp_Vcvt_Vcvtr_Rule_295_A1_P578_instance_)
  {}
};

// Neutral case:
// inst(19:16)=001x & inst(7:6)=x1 & inst(31:0)=xxxxxxxxxxxxxxxxxxxxxxx0xxxxxxxx
//    = CondVfpOp {'constraints': ,
//     'rule': 'Vcvtb_Vcvtt_Rule_300_A1_P588'}
//
// Representative case:
// opc2(19:16)=001x & opc3(7:6)=x1 & $pattern(31:0)=xxxxxxxxxxxxxxxxxxxxxxx0xxxxxxxx
//    = CondVfpOp {constraints: ,
//     rule: Vcvtb_Vcvtt_Rule_300_A1_P588}
class CondVfpOpTester_Case8
    : public CondVfpOpTesterCase8 {
 public:
  CondVfpOpTester_Case8()
    : CondVfpOpTesterCase8(
      state_.CondVfpOp_Vcvtb_Vcvtt_Rule_300_A1_P588_instance_)
  {}
};

// Neutral case:
// inst(19:16)=101x & inst(7:6)=x1
//    = CondVfpOp {'constraints': ,
//     'rule': 'Vcvt_Rule_297_A1_P582'}
//
// Representative case:
// opc2(19:16)=101x & opc3(7:6)=x1
//    = CondVfpOp {constraints: ,
//     rule: Vcvt_Rule_297_A1_P582}
class CondVfpOpTester_Case9
    : public CondVfpOpTesterCase9 {
 public:
  CondVfpOpTester_Case9()
    : CondVfpOpTesterCase9(
      state_.CondVfpOp_Vcvt_Rule_297_A1_P582_instance_)
  {}
};

// Neutral case:
// inst(19:16)=110x & inst(7:6)=x1
//    = CondVfpOp {'constraints': ,
//     'rule': 'Vcvt_Vcvtr_Rule_295_A1_P578'}
//
// Representative case:
// opc2(19:16)=110x & opc3(7:6)=x1
//    = CondVfpOp {constraints: ,
//     rule: Vcvt_Vcvtr_Rule_295_A1_P578}
class CondVfpOpTester_Case10
    : public CondVfpOpTesterCase10 {
 public:
  CondVfpOpTester_Case10()
    : CondVfpOpTesterCase10(
      state_.CondVfpOp_Vcvt_Vcvtr_Rule_295_A1_P578_instance_)
  {}
};

// Neutral case:
// inst(19:16)=111x & inst(7:6)=x1
//    = CondVfpOp {'constraints': ,
//     'rule': 'Vcvt_Rule_297_A1_P582'}
//
// Representative case:
// opc2(19:16)=111x & opc3(7:6)=x1
//    = CondVfpOp {constraints: ,
//     rule: Vcvt_Rule_297_A1_P582}
class CondVfpOpTester_Case11
    : public CondVfpOpTesterCase11 {
 public:
  CondVfpOpTester_Case11()
    : CondVfpOpTesterCase11(
      state_.CondVfpOp_Vcvt_Rule_297_A1_P582_instance_)
  {}
};

// Neutral case:
// inst(23:20)=0x00
//    = CondVfpOp {'constraints': ,
//     'rule': 'Vmla_vmls_Rule_423_A2_P636'}
//
// Representative case:
// opc1(23:20)=0x00
//    = CondVfpOp {constraints: ,
//     rule: Vmla_vmls_Rule_423_A2_P636}
class CondVfpOpTester_Case12
    : public CondVfpOpTesterCase12 {
 public:
  CondVfpOpTester_Case12()
    : CondVfpOpTesterCase12(
      state_.CondVfpOp_Vmla_vmls_Rule_423_A2_P636_instance_)
  {}
};

// Neutral case:
// inst(23:20)=0x01
//    = CondVfpOp {'constraints': ,
//     'rule': 'Vnmla_vnmls_Rule_343_A1_P674'}
//
// Representative case:
// opc1(23:20)=0x01
//    = CondVfpOp {constraints: ,
//     rule: Vnmla_vnmls_Rule_343_A1_P674}
class CondVfpOpTester_Case13
    : public CondVfpOpTesterCase13 {
 public:
  CondVfpOpTester_Case13()
    : CondVfpOpTesterCase13(
      state_.CondVfpOp_Vnmla_vnmls_Rule_343_A1_P674_instance_)
  {}
};

// Neutral case:
// inst(23:20)=0x10 & inst(7:6)=x0
//    = CondVfpOp {'constraints': ,
//     'rule': 'Vmul_Rule_338_A2_P664'}
//
// Representative case:
// opc1(23:20)=0x10 & opc3(7:6)=x0
//    = CondVfpOp {constraints: ,
//     rule: Vmul_Rule_338_A2_P664}
class CondVfpOpTester_Case14
    : public CondVfpOpTesterCase14 {
 public:
  CondVfpOpTester_Case14()
    : CondVfpOpTesterCase14(
      state_.CondVfpOp_Vmul_Rule_338_A2_P664_instance_)
  {}
};

// Neutral case:
// inst(23:20)=0x10 & inst(7:6)=x1
//    = CondVfpOp {'constraints': ,
//     'rule': 'Vnmul_Rule_343_A2_P674'}
//
// Representative case:
// opc1(23:20)=0x10 & opc3(7:6)=x1
//    = CondVfpOp {constraints: ,
//     rule: Vnmul_Rule_343_A2_P674}
class CondVfpOpTester_Case15
    : public CondVfpOpTesterCase15 {
 public:
  CondVfpOpTester_Case15()
    : CondVfpOpTesterCase15(
      state_.CondVfpOp_Vnmul_Rule_343_A2_P674_instance_)
  {}
};

// Neutral case:
// inst(23:20)=0x11 & inst(7:6)=x0
//    = CondVfpOp {'constraints': ,
//     'rule': 'Vadd_Rule_271_A2_P536'}
//
// Representative case:
// opc1(23:20)=0x11 & opc3(7:6)=x0
//    = CondVfpOp {constraints: ,
//     rule: Vadd_Rule_271_A2_P536}
class CondVfpOpTester_Case16
    : public CondVfpOpTesterCase16 {
 public:
  CondVfpOpTester_Case16()
    : CondVfpOpTesterCase16(
      state_.CondVfpOp_Vadd_Rule_271_A2_P536_instance_)
  {}
};

// Neutral case:
// inst(23:20)=0x11 & inst(7:6)=x1
//    = CondVfpOp {'constraints': ,
//     'rule': 'Vsub_Rule_402_A2_P790'}
//
// Representative case:
// opc1(23:20)=0x11 & opc3(7:6)=x1
//    = CondVfpOp {constraints: ,
//     rule: Vsub_Rule_402_A2_P790}
class CondVfpOpTester_Case17
    : public CondVfpOpTesterCase17 {
 public:
  CondVfpOpTester_Case17()
    : CondVfpOpTesterCase17(
      state_.CondVfpOp_Vsub_Rule_402_A2_P790_instance_)
  {}
};

// Neutral case:
// inst(23:20)=1x00 & inst(7:6)=x0
//    = CondVfpOp {'constraints': ,
//     'rule': 'Vdiv_Rule_301_A1_P590'}
//
// Representative case:
// opc1(23:20)=1x00 & opc3(7:6)=x0
//    = CondVfpOp {constraints: ,
//     rule: Vdiv_Rule_301_A1_P590}
class CondVfpOpTester_Case18
    : public CondVfpOpTesterCase18 {
 public:
  CondVfpOpTester_Case18()
    : CondVfpOpTesterCase18(
      state_.CondVfpOp_Vdiv_Rule_301_A1_P590_instance_)
  {}
};

// Neutral case:
// inst(23:20)=1x01
//    = CondVfpOp {'constraints': ,
//     'rule': 'Vfnma_vfnms_Rule_A1'}
//
// Representative case:
// opc1(23:20)=1x01
//    = CondVfpOp {constraints: ,
//     rule: Vfnma_vfnms_Rule_A1}
class CondVfpOpTester_Case19
    : public CondVfpOpTesterCase19 {
 public:
  CondVfpOpTester_Case19()
    : CondVfpOpTesterCase19(
      state_.CondVfpOp_Vfnma_vfnms_Rule_A1_instance_)
  {}
};

// Neutral case:
// inst(23:20)=1x10
//    = CondVfpOp {'constraints': ,
//     'rule': 'Vfma_vfms_Rule_A1'}
//
// Representative case:
// opc1(23:20)=1x10
//    = CondVfpOp {constraints: ,
//     rule: Vfma_vfms_Rule_A1}
class CondVfpOpTester_Case20
    : public CondVfpOpTesterCase20 {
 public:
  CondVfpOpTester_Case20()
    : CondVfpOpTesterCase20(
      state_.CondVfpOp_Vfma_vfms_Rule_A1_instance_)
  {}
};

// Neutral case:
// inst(7:6)=x0 & inst(31:0)=xxxxxxxxxxxxxxxxxxxxxxxx0x0xxxxx
//    = CondVfpOp {'constraints': ,
//     'rule': 'Vmov_Rule_326_A2_P640'}
//
// Representative case:
// opc3(7:6)=x0 & $pattern(31:0)=xxxxxxxxxxxxxxxxxxxxxxxx0x0xxxxx
//    = CondVfpOp {constraints: ,
//     rule: Vmov_Rule_326_A2_P640}
class CondVfpOpTester_Case21
    : public CondVfpOpTesterCase21 {
 public:
  CondVfpOpTester_Case21()
    : CondVfpOpTesterCase21(
      state_.CondVfpOp_Vmov_Rule_326_A2_P640_instance_)
  {}
};

// Defines a gtest testing harness for tests.
class Arm32DecoderStateTests : public ::testing::Test {
 protected:
  Arm32DecoderStateTests() {}
};

// The following functions test each pattern specified in parse
// decoder tables.

// Neutral case:
// inst(19:16)=0000 & inst(7:6)=01
//    = CondVfpOp => VfpOp {'constraints': ,
//     'pattern': 'cccc11101d110000dddd101s01m0mmmm',
//     'rule': 'Vmov_Rule_327_A2_P642'}
//
// Representative case:
// opc2(19:16)=0000 & opc3(7:6)=01
//    = CondVfpOp => VfpOp {constraints: ,
//     pattern: cccc11101d110000dddd101s01m0mmmm,
//     rule: Vmov_Rule_327_A2_P642}
TEST_F(Arm32DecoderStateTests,
       CondVfpOpTester_Case0_TestCase0) {
  CondVfpOpTester_Case0 baseline_tester;
  NamedVfpOp_Vmov_Rule_327_A2_P642 actual;
  ActualVsBaselineTester a_vs_b_tester(actual, baseline_tester);
  a_vs_b_tester.Test("cccc11101d110000dddd101s01m0mmmm");
}

// Neutral case:
// inst(19:16)=0000 & inst(7:6)=11
//    = CondVfpOp => VfpOp {'constraints': ,
//     'pattern': 'cccc11101d110000dddd101s11m0mmmm',
//     'rule': 'Vabs_Rule_269_A2_P532'}
//
// Representative case:
// opc2(19:16)=0000 & opc3(7:6)=11
//    = CondVfpOp => VfpOp {constraints: ,
//     pattern: cccc11101d110000dddd101s11m0mmmm,
//     rule: Vabs_Rule_269_A2_P532}
TEST_F(Arm32DecoderStateTests,
       CondVfpOpTester_Case1_TestCase1) {
  CondVfpOpTester_Case1 baseline_tester;
  NamedVfpOp_Vabs_Rule_269_A2_P532 actual;
  ActualVsBaselineTester a_vs_b_tester(actual, baseline_tester);
  a_vs_b_tester.Test("cccc11101d110000dddd101s11m0mmmm");
}

// Neutral case:
// inst(19:16)=0001 & inst(7:6)=01
//    = CondVfpOp => VfpOp {'constraints': ,
//     'pattern': 'cccc11101d110001dddd101s01m0mmmm',
//     'rule': 'Vneg_Rule_342_A2_P672'}
//
// Representative case:
// opc2(19:16)=0001 & opc3(7:6)=01
//    = CondVfpOp => VfpOp {constraints: ,
//     pattern: cccc11101d110001dddd101s01m0mmmm,
//     rule: Vneg_Rule_342_A2_P672}
TEST_F(Arm32DecoderStateTests,
       CondVfpOpTester_Case2_TestCase2) {
  CondVfpOpTester_Case2 baseline_tester;
  NamedVfpOp_Vneg_Rule_342_A2_P672 actual;
  ActualVsBaselineTester a_vs_b_tester(actual, baseline_tester);
  a_vs_b_tester.Test("cccc11101d110001dddd101s01m0mmmm");
}

// Neutral case:
// inst(19:16)=0001 & inst(7:6)=11
//    = CondVfpOp => VfpOp {'constraints': ,
//     'pattern': 'cccc11101d110001dddd101s11m0mmmm',
//     'rule': 'Vsqrt_Rule_388_A1_P762'}
//
// Representative case:
// opc2(19:16)=0001 & opc3(7:6)=11
//    = CondVfpOp => VfpOp {constraints: ,
//     pattern: cccc11101d110001dddd101s11m0mmmm,
//     rule: Vsqrt_Rule_388_A1_P762}
TEST_F(Arm32DecoderStateTests,
       CondVfpOpTester_Case3_TestCase3) {
  CondVfpOpTester_Case3 baseline_tester;
  NamedVfpOp_Vsqrt_Rule_388_A1_P762 actual;
  ActualVsBaselineTester a_vs_b_tester(actual, baseline_tester);
  a_vs_b_tester.Test("cccc11101d110001dddd101s11m0mmmm");
}

// Neutral case:
// inst(19:16)=0100 & inst(7:6)=x1
//    = CondVfpOp => VfpOp {'constraints': ,
//     'pattern': 'cccc11101d110100dddd101se1m0mmmm',
//     'rule': 'Vcmp_Vcmpe_Rule_A1'}
//
// Representative case:
// opc2(19:16)=0100 & opc3(7:6)=x1
//    = CondVfpOp => VfpOp {constraints: ,
//     pattern: cccc11101d110100dddd101se1m0mmmm,
//     rule: Vcmp_Vcmpe_Rule_A1}
TEST_F(Arm32DecoderStateTests,
       CondVfpOpTester_Case4_TestCase4) {
  CondVfpOpTester_Case4 baseline_tester;
  NamedVfpOp_Vcmp_Vcmpe_Rule_A1 actual;
  ActualVsBaselineTester a_vs_b_tester(actual, baseline_tester);
  a_vs_b_tester.Test("cccc11101d110100dddd101se1m0mmmm");
}

// Neutral case:
// inst(19:16)=0101 & inst(7:6)=x1 & inst(31:0)=xxxxxxxxxxxxxxxxxxxxxxxxxx0x0000
//    = CondVfpOp => VfpOp {'constraints': ,
//     'pattern': 'cccc11101d110101dddd101se1000000',
//     'rule': 'Vcmp_Vcmpe_Rule_A2'}
//
// Representative case:
// opc2(19:16)=0101 & opc3(7:6)=x1 & $pattern(31:0)=xxxxxxxxxxxxxxxxxxxxxxxxxx0x0000
//    = CondVfpOp => VfpOp {constraints: ,
//     pattern: cccc11101d110101dddd101se1000000,
//     rule: Vcmp_Vcmpe_Rule_A2}
TEST_F(Arm32DecoderStateTests,
       CondVfpOpTester_Case5_TestCase5) {
  CondVfpOpTester_Case5 baseline_tester;
  NamedVfpOp_Vcmp_Vcmpe_Rule_A2 actual;
  ActualVsBaselineTester a_vs_b_tester(actual, baseline_tester);
  a_vs_b_tester.Test("cccc11101d110101dddd101se1000000");
}

// Neutral case:
// inst(19:16)=0111 & inst(7:6)=11
//    = CondVfpOp => VfpOp {'constraints': ,
//     'pattern': 'cccc11101d110111dddd101s11m0mmmm',
//     'rule': 'Vcvt_Rule_298_A1_P584'}
//
// Representative case:
// opc2(19:16)=0111 & opc3(7:6)=11
//    = CondVfpOp => VfpOp {constraints: ,
//     pattern: cccc11101d110111dddd101s11m0mmmm,
//     rule: Vcvt_Rule_298_A1_P584}
TEST_F(Arm32DecoderStateTests,
       CondVfpOpTester_Case6_TestCase6) {
  CondVfpOpTester_Case6 baseline_tester;
  NamedVfpOp_Vcvt_Rule_298_A1_P584 actual;
  ActualVsBaselineTester a_vs_b_tester(actual, baseline_tester);
  a_vs_b_tester.Test("cccc11101d110111dddd101s11m0mmmm");
}

// Neutral case:
// inst(19:16)=1000 & inst(7:6)=x1
//    = CondVfpOp => VfpOp {'constraints': ,
//     'pattern': 'cccc11101d111000dddd101sp1m0mmmm',
//     'rule': 'Vcvt_Vcvtr_Rule_295_A1_P578'}
//
// Representative case:
// opc2(19:16)=1000 & opc3(7:6)=x1
//    = CondVfpOp => VfpOp {constraints: ,
//     pattern: cccc11101d111000dddd101sp1m0mmmm,
//     rule: Vcvt_Vcvtr_Rule_295_A1_P578}
TEST_F(Arm32DecoderStateTests,
       CondVfpOpTester_Case7_TestCase7) {
  CondVfpOpTester_Case7 baseline_tester;
  NamedVfpOp_Vcvt_Vcvtr_Rule_295_A1_P578 actual;
  ActualVsBaselineTester a_vs_b_tester(actual, baseline_tester);
  a_vs_b_tester.Test("cccc11101d111000dddd101sp1m0mmmm");
}

// Neutral case:
// inst(19:16)=001x & inst(7:6)=x1 & inst(31:0)=xxxxxxxxxxxxxxxxxxxxxxx0xxxxxxxx
//    = CondVfpOp => VfpOp {'constraints': ,
//     'pattern': 'cccc11101d11001odddd1010t1m0mmmm',
//     'rule': 'Vcvtb_Vcvtt_Rule_300_A1_P588'}
//
// Representative case:
// opc2(19:16)=001x & opc3(7:6)=x1 & $pattern(31:0)=xxxxxxxxxxxxxxxxxxxxxxx0xxxxxxxx
//    = CondVfpOp => VfpOp {constraints: ,
//     pattern: cccc11101d11001odddd1010t1m0mmmm,
//     rule: Vcvtb_Vcvtt_Rule_300_A1_P588}
TEST_F(Arm32DecoderStateTests,
       CondVfpOpTester_Case8_TestCase8) {
  CondVfpOpTester_Case8 baseline_tester;
  NamedVfpOp_Vcvtb_Vcvtt_Rule_300_A1_P588 actual;
  ActualVsBaselineTester a_vs_b_tester(actual, baseline_tester);
  a_vs_b_tester.Test("cccc11101d11001odddd1010t1m0mmmm");
}

// Neutral case:
// inst(19:16)=101x & inst(7:6)=x1
//    = CondVfpOp => VfpOp {'constraints': ,
//     'pattern': 'cccc11101d11101udddd101fx1i0iiii',
//     'rule': 'Vcvt_Rule_297_A1_P582'}
//
// Representative case:
// opc2(19:16)=101x & opc3(7:6)=x1
//    = CondVfpOp => VfpOp {constraints: ,
//     pattern: cccc11101d11101udddd101fx1i0iiii,
//     rule: Vcvt_Rule_297_A1_P582}
TEST_F(Arm32DecoderStateTests,
       CondVfpOpTester_Case9_TestCase9) {
  CondVfpOpTester_Case9 baseline_tester;
  NamedVfpOp_Vcvt_Rule_297_A1_P582 actual;
  ActualVsBaselineTester a_vs_b_tester(actual, baseline_tester);
  a_vs_b_tester.Test("cccc11101d11101udddd101fx1i0iiii");
}

// Neutral case:
// inst(19:16)=110x & inst(7:6)=x1
//    = CondVfpOp => VfpOp {'constraints': ,
//     'pattern': 'cccc11101d11110xdddd101sp1m0mmmm',
//     'rule': 'Vcvt_Vcvtr_Rule_295_A1_P578'}
//
// Representative case:
// opc2(19:16)=110x & opc3(7:6)=x1
//    = CondVfpOp => VfpOp {constraints: ,
//     pattern: cccc11101d11110xdddd101sp1m0mmmm,
//     rule: Vcvt_Vcvtr_Rule_295_A1_P578}
TEST_F(Arm32DecoderStateTests,
       CondVfpOpTester_Case10_TestCase10) {
  CondVfpOpTester_Case10 baseline_tester;
  NamedVfpOp_Vcvt_Vcvtr_Rule_295_A1_P578 actual;
  ActualVsBaselineTester a_vs_b_tester(actual, baseline_tester);
  a_vs_b_tester.Test("cccc11101d11110xdddd101sp1m0mmmm");
}

// Neutral case:
// inst(19:16)=111x & inst(7:6)=x1
//    = CondVfpOp => VfpOp {'constraints': ,
//     'pattern': 'cccc11101d11111udddd101fx1i0iiii',
//     'rule': 'Vcvt_Rule_297_A1_P582'}
//
// Representative case:
// opc2(19:16)=111x & opc3(7:6)=x1
//    = CondVfpOp => VfpOp {constraints: ,
//     pattern: cccc11101d11111udddd101fx1i0iiii,
//     rule: Vcvt_Rule_297_A1_P582}
TEST_F(Arm32DecoderStateTests,
       CondVfpOpTester_Case11_TestCase11) {
  CondVfpOpTester_Case11 baseline_tester;
  NamedVfpOp_Vcvt_Rule_297_A1_P582 actual;
  ActualVsBaselineTester a_vs_b_tester(actual, baseline_tester);
  a_vs_b_tester.Test("cccc11101d11111udddd101fx1i0iiii");
}

// Neutral case:
// inst(23:20)=0x00
//    = CondVfpOp => VfpOp {'constraints': ,
//     'pattern': 'cccc11100d00nnnndddd101snom0mmmm',
//     'rule': 'Vmla_vmls_Rule_423_A2_P636'}
//
// Representative case:
// opc1(23:20)=0x00
//    = CondVfpOp => VfpOp {constraints: ,
//     pattern: cccc11100d00nnnndddd101snom0mmmm,
//     rule: Vmla_vmls_Rule_423_A2_P636}
TEST_F(Arm32DecoderStateTests,
       CondVfpOpTester_Case12_TestCase12) {
  CondVfpOpTester_Case12 baseline_tester;
  NamedVfpOp_Vmla_vmls_Rule_423_A2_P636 actual;
  ActualVsBaselineTester a_vs_b_tester(actual, baseline_tester);
  a_vs_b_tester.Test("cccc11100d00nnnndddd101snom0mmmm");
}

// Neutral case:
// inst(23:20)=0x01
//    = CondVfpOp => VfpOp {'constraints': ,
//     'pattern': 'cccc11100d01nnnndddd101snom0mmmm',
//     'rule': 'Vnmla_vnmls_Rule_343_A1_P674'}
//
// Representative case:
// opc1(23:20)=0x01
//    = CondVfpOp => VfpOp {constraints: ,
//     pattern: cccc11100d01nnnndddd101snom0mmmm,
//     rule: Vnmla_vnmls_Rule_343_A1_P674}
TEST_F(Arm32DecoderStateTests,
       CondVfpOpTester_Case13_TestCase13) {
  CondVfpOpTester_Case13 baseline_tester;
  NamedVfpOp_Vnmla_vnmls_Rule_343_A1_P674 actual;
  ActualVsBaselineTester a_vs_b_tester(actual, baseline_tester);
  a_vs_b_tester.Test("cccc11100d01nnnndddd101snom0mmmm");
}

// Neutral case:
// inst(23:20)=0x10 & inst(7:6)=x0
//    = CondVfpOp => VfpOp {'constraints': ,
//     'pattern': 'cccc11100d10nnnndddd101sn0m0mmmm',
//     'rule': 'Vmul_Rule_338_A2_P664'}
//
// Representative case:
// opc1(23:20)=0x10 & opc3(7:6)=x0
//    = CondVfpOp => VfpOp {constraints: ,
//     pattern: cccc11100d10nnnndddd101sn0m0mmmm,
//     rule: Vmul_Rule_338_A2_P664}
TEST_F(Arm32DecoderStateTests,
       CondVfpOpTester_Case14_TestCase14) {
  CondVfpOpTester_Case14 baseline_tester;
  NamedVfpOp_Vmul_Rule_338_A2_P664 actual;
  ActualVsBaselineTester a_vs_b_tester(actual, baseline_tester);
  a_vs_b_tester.Test("cccc11100d10nnnndddd101sn0m0mmmm");
}

// Neutral case:
// inst(23:20)=0x10 & inst(7:6)=x1
//    = CondVfpOp => VfpOp {'constraints': ,
//     'pattern': 'cccc11100d10nnnndddd101sn1m0mmmm',
//     'rule': 'Vnmul_Rule_343_A2_P674'}
//
// Representative case:
// opc1(23:20)=0x10 & opc3(7:6)=x1
//    = CondVfpOp => VfpOp {constraints: ,
//     pattern: cccc11100d10nnnndddd101sn1m0mmmm,
//     rule: Vnmul_Rule_343_A2_P674}
TEST_F(Arm32DecoderStateTests,
       CondVfpOpTester_Case15_TestCase15) {
  CondVfpOpTester_Case15 baseline_tester;
  NamedVfpOp_Vnmul_Rule_343_A2_P674 actual;
  ActualVsBaselineTester a_vs_b_tester(actual, baseline_tester);
  a_vs_b_tester.Test("cccc11100d10nnnndddd101sn1m0mmmm");
}

// Neutral case:
// inst(23:20)=0x11 & inst(7:6)=x0
//    = CondVfpOp => VfpOp {'constraints': ,
//     'pattern': 'cccc11100d11nnnndddd101sn0m0mmmm',
//     'rule': 'Vadd_Rule_271_A2_P536'}
//
// Representative case:
// opc1(23:20)=0x11 & opc3(7:6)=x0
//    = CondVfpOp => VfpOp {constraints: ,
//     pattern: cccc11100d11nnnndddd101sn0m0mmmm,
//     rule: Vadd_Rule_271_A2_P536}
TEST_F(Arm32DecoderStateTests,
       CondVfpOpTester_Case16_TestCase16) {
  CondVfpOpTester_Case16 baseline_tester;
  NamedVfpOp_Vadd_Rule_271_A2_P536 actual;
  ActualVsBaselineTester a_vs_b_tester(actual, baseline_tester);
  a_vs_b_tester.Test("cccc11100d11nnnndddd101sn0m0mmmm");
}

// Neutral case:
// inst(23:20)=0x11 & inst(7:6)=x1
//    = CondVfpOp => VfpOp {'constraints': ,
//     'pattern': 'cccc11100d11nnnndddd101sn1m0mmmm',
//     'rule': 'Vsub_Rule_402_A2_P790'}
//
// Representative case:
// opc1(23:20)=0x11 & opc3(7:6)=x1
//    = CondVfpOp => VfpOp {constraints: ,
//     pattern: cccc11100d11nnnndddd101sn1m0mmmm,
//     rule: Vsub_Rule_402_A2_P790}
TEST_F(Arm32DecoderStateTests,
       CondVfpOpTester_Case17_TestCase17) {
  CondVfpOpTester_Case17 baseline_tester;
  NamedVfpOp_Vsub_Rule_402_A2_P790 actual;
  ActualVsBaselineTester a_vs_b_tester(actual, baseline_tester);
  a_vs_b_tester.Test("cccc11100d11nnnndddd101sn1m0mmmm");
}

// Neutral case:
// inst(23:20)=1x00 & inst(7:6)=x0
//    = CondVfpOp => VfpOp {'constraints': ,
//     'pattern': 'cccc11101d00nnnndddd101sn0m0mmmm',
//     'rule': 'Vdiv_Rule_301_A1_P590'}
//
// Representative case:
// opc1(23:20)=1x00 & opc3(7:6)=x0
//    = CondVfpOp => VfpOp {constraints: ,
//     pattern: cccc11101d00nnnndddd101sn0m0mmmm,
//     rule: Vdiv_Rule_301_A1_P590}
TEST_F(Arm32DecoderStateTests,
       CondVfpOpTester_Case18_TestCase18) {
  CondVfpOpTester_Case18 baseline_tester;
  NamedVfpOp_Vdiv_Rule_301_A1_P590 actual;
  ActualVsBaselineTester a_vs_b_tester(actual, baseline_tester);
  a_vs_b_tester.Test("cccc11101d00nnnndddd101sn0m0mmmm");
}

// Neutral case:
// inst(23:20)=1x01
//    = CondVfpOp => VfpOp {'constraints': ,
//     'pattern': 'cccc11101d01nnnndddd101snom0mmmm',
//     'rule': 'Vfnma_vfnms_Rule_A1'}
//
// Representative case:
// opc1(23:20)=1x01
//    = CondVfpOp => VfpOp {constraints: ,
//     pattern: cccc11101d01nnnndddd101snom0mmmm,
//     rule: Vfnma_vfnms_Rule_A1}
TEST_F(Arm32DecoderStateTests,
       CondVfpOpTester_Case19_TestCase19) {
  CondVfpOpTester_Case19 baseline_tester;
  NamedVfpOp_Vfnma_vfnms_Rule_A1 actual;
  ActualVsBaselineTester a_vs_b_tester(actual, baseline_tester);
  a_vs_b_tester.Test("cccc11101d01nnnndddd101snom0mmmm");
}

// Neutral case:
// inst(23:20)=1x10
//    = CondVfpOp => VfpOp {'constraints': ,
//     'pattern': 'cccc11101d10nnnndddd101snom0mmmm',
//     'rule': 'Vfma_vfms_Rule_A1'}
//
// Representative case:
// opc1(23:20)=1x10
//    = CondVfpOp => VfpOp {constraints: ,
//     pattern: cccc11101d10nnnndddd101snom0mmmm,
//     rule: Vfma_vfms_Rule_A1}
TEST_F(Arm32DecoderStateTests,
       CondVfpOpTester_Case20_TestCase20) {
  CondVfpOpTester_Case20 baseline_tester;
  NamedVfpOp_Vfma_vfms_Rule_A1 actual;
  ActualVsBaselineTester a_vs_b_tester(actual, baseline_tester);
  a_vs_b_tester.Test("cccc11101d10nnnndddd101snom0mmmm");
}

// Neutral case:
// inst(7:6)=x0 & inst(31:0)=xxxxxxxxxxxxxxxxxxxxxxxx0x0xxxxx
//    = CondVfpOp => VfpOp {'constraints': ,
//     'pattern': 'cccc11101d11iiiidddd101s0000iiii',
//     'rule': 'Vmov_Rule_326_A2_P640'}
//
// Representative case:
// opc3(7:6)=x0 & $pattern(31:0)=xxxxxxxxxxxxxxxxxxxxxxxx0x0xxxxx
//    = CondVfpOp => VfpOp {constraints: ,
//     pattern: cccc11101d11iiiidddd101s0000iiii,
//     rule: Vmov_Rule_326_A2_P640}
TEST_F(Arm32DecoderStateTests,
       CondVfpOpTester_Case21_TestCase21) {
  CondVfpOpTester_Case21 baseline_tester;
  NamedVfpOp_Vmov_Rule_326_A2_P640 actual;
  ActualVsBaselineTester a_vs_b_tester(actual, baseline_tester);
  a_vs_b_tester.Test("cccc11101d11iiiidddd101s0000iiii");
}

}  // namespace nacl_arm_test

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}