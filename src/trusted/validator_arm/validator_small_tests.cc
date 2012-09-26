/*
 * Copyright (c) 2012 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef NACL_TRUSTED_BUT_NOT_TCB
#error This file is not meant for use in the TCB
#endif

/*
 * Small unit tests for the ARM validator
 *
 * Also see validator_large_tests.cc,
 * and validator_tests.h for the testing infrastructure.
 */

#include "native_client/src/trusted/validator_arm/validator_tests.h"

using nacl_val_arm_test::ProblemRecord;
using nacl_val_arm_test::ProblemSpy;
using nacl_val_arm_test::ValidatorTests;
using nacl_val_arm_test::kDefaultBaseAddr;
using nacl_val_arm_test::kCodeRegionSize;
using nacl_val_arm_test::kDataRegionSize;
using nacl_val_arm_test::kAbiReadOnlyRegisters;
using nacl_val_arm_test::kAbiDataAddrRegisters;
using nacl_val_arm_test::arm_inst;

namespace {

/*
 * Primitive tests checking various constructor properties.  Any of these
 * failing would be a very bad sign indeed.
 */

TEST_F(ValidatorTests, RecognizesDataAddressRegisters) {
  // Note that the logic below needs to be kept in sync with the definition
  // of kAbiDataAddrRegisters at the top of this file.
  //
  // This test is pretty trivial -- we can exercise the data_address_register
  // functionality more deeply with pattern tests below.
  for (int i = 0; i < 16; i++) {
    Register r(i);
    if (r.Equals(nacl_arm_dec::kRegisterStack)) {
      EXPECT_TRUE(_validator.is_data_address_register(r))
          << "Stack pointer must be a data address register.";
    } else {
      EXPECT_FALSE(_validator.is_data_address_register(r))
          << "Only the stack pointer must be a data address register.";
    }
  }
}

TEST_F(ValidatorTests, GeneratesCorrectMasksFromSizes) {
  EXPECT_EQ(0xC0000000, _validator.data_address_mask());
  EXPECT_EQ(0xE000000F, _validator.code_address_mask());

  // Reinitialize the validator to test a different bundle size.
  _validator = SfiValidator(32,
                            kCodeRegionSize,
                            kDataRegionSize,
                            kAbiReadOnlyRegisters,
                            kAbiDataAddrRegisters);
  EXPECT_EQ(0xC0000000, _validator.data_address_mask())
      << "Changes in bundle size should not affect the data mask.";
  EXPECT_EQ(0xE000001F, _validator.code_address_mask())
      << "Changes in bundle size must affect the code mask.";
}

// Code validation tests

TEST_F(ValidatorTests, DirectBranchTargetCalculation) {
  const nacl_arm_dec::Arm32DecoderState decode_state;
  // Try decoding PC-relative branches from interesting PCs.
  uint32_t start_addrs[] = { 0x00000000, 0x00010000, 0x00020000, 0x06789abc,
                             0x12345678, 0x3fffffff, 0xdeadbeef, 0xff000000, };
  for (size_t a = 0; a < NACL_ARRAY_SIZE(start_addrs); ++a) {
    uint32_t start_addr = start_addrs[a];
    // All PC-relative branches supported by NaCl.
    arm_inst insts[] = {
      0xea000000,  // B PC+8+0
      0xeb000000,  // BL PC+8+0
    };
    for (arm_inst* inst = insts;
         inst < insts + NACL_ARRAY_SIZE(insts);
         ++inst) {
      for (Instruction::Condition cond = Instruction::EQ;
           cond <= Instruction::AL;
           cond = Instruction::Next(cond)) {
        *inst = ChangeCond(*inst, cond);
        for (int32_t imm = -2050; imm < 2050; ++imm) {
          // For all PC-relative branches that NaCl supports:
          //   imm24(23:0);
          //   imm32 = SignExtend(imm24:'00', 32);
          //   targetAddress = Align(PC,4) + imm32;
          // Where:
          //   The PC value of an instruction is its address plus 8 for an
          //   ARM instruction. The Align(PC, 4) value of an instruction is
          //   its PC value ANDed with 0xFFFFFFFC to force it to be
          //   word-aligned. There is no difference between the PC and
          //   Align(PC, 4) values for an ARM instruction.
          *inst = (*inst & 0xff000000) | ((imm >> 2) & 0x00ffffff);
          const uint8_t *bytes = reinterpret_cast<const uint8_t *>(inst);
          CodeSegment segment(bytes, start_addr, sizeof(arm_inst));
          nacl_arm_val::DecodedInstruction inst(start_addr, segment[start_addr],
                                                decode_state.decode(
                                                    segment[start_addr]));
          EXPECT_TRUE(inst.is_relative_branch());
          EXPECT_EQ(start_addr + 8 + (imm & 0xfffffffc), inst.branch_target());
        }
      }
    }
  }
}

// Here are examples of every form of safe store permitted in a Native Client
// program.  These stores have common properties:
//  1. The high nibble is 0, to allow tests to write an arbitrary predicate.
//  2. They address memory only through r1.
//  3. They do not do anything dumb, like try to alter SP or PC.
struct AnnotatedInstruction {
  arm_inst inst;
  const char *about;
};
static const AnnotatedInstruction examples_of_safe_stores[] = {
  // Single-register stores
  { 0x05810000, "str r0, [r1]: simple no-displacement store" },
  { 0x05810123, "str r0, [r1, #0x123]: positive displacement" },
  { 0x05010123, "str r0, [r1, #-0x123]: negative displacement" },
  { 0x05A10123, "str r0, [r1, #0x123]!: positive disp + writeback" },
  { 0x05210123, "str r0, [r1, #-0x123]!: negative disp + writeback" },
  { 0x04810123, "str r0, [r1], #0x123: positive post-indexing" },
  { 0x04010123, "str r0, [r1], #-0x123: negative post-indexing" },
  { 0x06810002, "str r0, [r1], r2: positive register post-indexing" },
  { 0x06010002, "str r0, [r1], -r2: negative register post-indexing" },

  // Two-register store
  { 0x01C120F0, "strd r2, r3, [r1]: basic 64-bit store" },
  { 0x01C124F2, "strd r2, r3, [r1, #42]: positive disp 64-bit store" },
  { 0x014124F2, "strd r2, r3, [r1, #-42]: negative disp 64-bit store" },
  { 0x01E124F2, "strd r2, r3, [r1, #42]!: positive disp 64-bit store + wb" },
  { 0x016124F2, "strd r2, r3, [r1, #-42]!: negative disp 64-bit store + wb" },
  { 0x00C124F2, "strd r2, r3, [r1], #42: post-inc 64-bit store" },
  { 0x004124F2, "strd r2, r3, [r1], #-42: post-dec 64-bit store" },

  // Store-exclusive
  { 0x01810F92, "strex r0, r2, [r1]: store exclusive" },

  // Store-multiple
  { 0x0881FFFF, "stm r1, { r0-r15 }: store multiple, no writeback" },
  // Note: can't store registers whose number is less than Rt when there is
  //       writeback. E.g. stm r1! { r0-r15 } is unknown.
  { 0x08A1FFFE, "stm r1!, { r1-r15 }: store multiple, writeback" },
  { 0x08A1FFFC, "stm r1!, { r2-r15 }: store multiple, writeback" },

  // Stores from the floating point / vector register file
  // These all compile to STC instructions.
  { 0x0D810B00, "vstr d0, [r1]: direct vector store" },
  { 0x0D810B99, "vstr d0, [r1, #0x99]: positive displacement vector store" },
  { 0x0D010B99, "vstr d0, [r1, #-0x99]: negative displacement vector store" },
  { 0x0C810B10, "vstmia r1, { d0-d7 }: no writeback" },
  { 0x0CA10B10, "vstmia r1!, { d0-d7 }: writeback" },
};

static const AnnotatedInstruction examples_of_safe_masks[] = {
  { 0x03C11103, "bic r1, r1, #0xC0000000: simple in-place mask (form 1)" },
  { 0x03C114C0, "bic r1, r1, #0xC0000000: simple in-place mask (form 2)" },
  { 0x03C314C0, "bic r1, r3, #0xC0000000: mask with register move" },
  { 0x03C114FF, "bic r1, r1, #0xFF000000: overzealous but correct mask" },
};

TEST_F(ValidatorTests, SafeMaskedStores) {
  // Produces many examples of masked stores using the safe store table (above)
  // and the list of possible masking instructions (below).
  //
  // Each mask instruction must leave a valid (data) address in r1.
  for (unsigned p = 0; p < 15; p++) {
    // Conditionally executed instructions have a top nibble of 0..14.
    // 15 is an escape sequence used to fit in additional encodings.
    arm_inst predicate = p << 28;

    for (unsigned m = 0; m < NACL_ARRAY_SIZE(examples_of_safe_masks); m++) {
      for (unsigned s = 0; s < NACL_ARRAY_SIZE(examples_of_safe_stores); s++) {
        ostringstream message;
        message << examples_of_safe_masks[m].about
                << ", "
                << examples_of_safe_stores[s].about
                << " (predicate #" << p << ")";
        arm_inst program[] = {
          examples_of_safe_masks[m].inst | predicate,
          examples_of_safe_stores[s].inst | predicate,
        };
        validation_should_pass2(program,
                                2,
                                kDefaultBaseAddr,
                                message.str());
      }
    }
  }
}

/* TODO(karl): Add these back once simd instructions are turned back on.
// These stores can't be predicated, so we must use a different, simpler
// fixture generator.
static const AnnotatedInstruction examples_of_safe_unconditional_stores[] = {
  // Vector stores
  { 0xF481A5AF, "vst2.16 {d10[2],d12[2]}, [r1]: simple vector store" },
  { 0xF401A64F, "vst1.16 {d10-d12}, [r1]: larger vector store" },
  { 0xF4010711, "vst1.8 {d0}, [r1, :64], r1: register post-increment" },
};

TEST_F(ValidatorTests, SafeUnconditionalMaskedStores) {
  // Produces many examples of unconditional masked stores using the safe
  // unconditional store table (above) and the list of possible masking
  // instructions (below).
  //
  // Each mask instruction must leave a valid (data) address in r1.

  // These instructions can't be predicated.
  arm_inst predicate = 0xE0000000;  // "always"

  for (unsigned m = 0; m < NACL_ARRAY_SIZE(examples_of_safe_masks); m++) {
    for (unsigned s = 0;
         s < NACL_ARRAY_SIZE(examples_of_safe_unconditional_stores);
         s++) {
      ostringstream message;
      message << examples_of_safe_masks[m].about
              << ", "
              << examples_of_safe_unconditional_stores[s].about;
      arm_inst program[] = {
        examples_of_safe_masks[m].inst | predicate,
        examples_of_safe_unconditional_stores[s].inst,
      };
      validation_should_pass2(program,
                              2,
                              kDefaultBaseAddr,
                              message.str());
    }
  }
}
*/

TEST_F(ValidatorTests, SafeConditionalStores) {
  // Produces many examples of conditional stores using the safe store table
  // (above) and the list of possible conditional guards (below).
  //
  // Each conditional guard must set the Z flag iff r1 contains a valid address.
  static const AnnotatedInstruction guards[] = {
    { 0x03110103, "tst r1, #0xC0000000: precise guard, GCC encoding" },
    { 0x031104C0, "tst r1, #0xC0000000: precise guard, alternative encoding" },
    { 0x031101C3, "tst r1, #0xF0000000: overzealous (but correct) guard" },
  };

  // Currently we only support *unconditional* conditional stores.
  // Meaning the guard is unconditional and the store is if-equal.
  arm_inst guard_predicate = 0xE0000000, store_predicate = 0x00000000;
  for (unsigned m = 0; m < NACL_ARRAY_SIZE(guards); m++) {
    for (unsigned s = 0; s < NACL_ARRAY_SIZE(examples_of_safe_stores); s++) {
      ostringstream message;
      message << guards[m].about
              << ", "
              << examples_of_safe_stores[s].about
              << " (predicate #" << guard_predicate << ")";
      arm_inst program[] = {
        guards[m].inst | guard_predicate,
        examples_of_safe_stores[s].inst | store_predicate,
      };
      validation_should_pass2(program,
                              2,
                              kDefaultBaseAddr,
                              message.str());
    }
  }
}


TEST_F(ValidatorTests, InvalidMasksOnSafeStores) {
  static const AnnotatedInstruction examples_of_invalid_masks[] = {
    { 0x01A01003, "mov r1, r3: not even a mask" },
    { 0x03C31000, "bic r1, r3, #0: doesn't mask anything" },
    { 0x03C31102, "bic r1, r3, #0x80000000: doesn't mask enough bits" },
    { 0x03C311C1, "bic r1, r3, #0x70000000: masks the wrong bits" },
  };

  for (unsigned p = 0; p < 15; p++) {
    // Conditionally executed instructions have a top nibble of 0..14.
    // 15 is an escape sequence used to fit in additional encodings.
    arm_inst predicate = p << 28;

    for (unsigned m = 0; m < NACL_ARRAY_SIZE(examples_of_invalid_masks); m++) {
      for (unsigned s = 0; s < NACL_ARRAY_SIZE(examples_of_safe_stores); s++) {
        ostringstream message;
        message << examples_of_invalid_masks[m].about
                << ", "
                << examples_of_safe_stores[s].about
                << " (predicate #" << p << ")";
        arm_inst program[] = {
          examples_of_invalid_masks[m].inst | predicate,
          examples_of_safe_stores[s].inst | predicate,
        };

        vector<ProblemRecord> problems =
            validation_should_fail(program,
                                   NACL_ARRAY_SIZE(program),
                                   kDefaultBaseAddr,
                                   message.str());

        // EXPECT/continue rather than ASSERT so that we run the other cases.
        EXPECT_EQ(1U, problems.size());
        if (problems.size() != 1) continue;

        ProblemRecord first = problems[0];
        EXPECT_EQ(kDefaultBaseAddr + 4, first.vaddr())
            << "Problem report must point to the store: "
            << message.str();
        EXPECT_NE(nacl_arm_val::kReportProblemSafety, first.method())
            << "Store should not be unsafe even though mask is bogus: "
            << message.str();
        EXPECT_EQ(nacl_arm_val::kProblemUnsafeLoadStore, first.problem())
            << message;
      }
    }
  }
}

TEST_F(ValidatorTests, InvalidGuardsOnSafeStores) {
  static const AnnotatedInstruction invalid_guards[] = {
    { 0x03110100, "tst r1, #0: always sets Z" },
    { 0x03110102, "tst r1, #0x80000000: doesn't test enough bits" },
    { 0x031101C1, "tst r1, #0x70000000: doesn't test the right bits" },
    { 0x01A01003, "mov r1, r3: not even a test" },
    { 0x03310103, "teq r1, #0xC0000000: does the inverse of what we want" },
    { 0x03510103, "cmp r1, #0xC0000000: does the inverse of what we want" },
  };

  // We don't currently support conditional versions of the conditional guard.
  //
  // TODO(cbiffle): verify this in the test
  static const arm_inst guard_predicate = 0xE0000000;  // unconditional
  static const arm_inst store_predicate = 0x00000000;  // if-equal

  for (unsigned m = 0; m < NACL_ARRAY_SIZE(invalid_guards); m++) {
    for (unsigned s = 0; s < NACL_ARRAY_SIZE(examples_of_safe_stores); s++) {
      ostringstream message;
      message << invalid_guards[m].about
              << ", "
              << examples_of_safe_stores[s].about;
      arm_inst program[] = {
        invalid_guards[m].inst | guard_predicate,
        examples_of_safe_stores[s].inst | store_predicate,
      };

      vector<ProblemRecord> problems =
          validation_should_fail(program,
                                 NACL_ARRAY_SIZE(program),
                                 kDefaultBaseAddr,
                                 message.str());

      // EXPECT/continue rather than ASSERT so that we run the other cases.
      EXPECT_EQ(1U, problems.size());
      if (problems.size() != 1) continue;

      ProblemRecord first = problems[0];
      EXPECT_EQ(kDefaultBaseAddr + 4, first.vaddr())
          << "Problem report must point to the store: "
          << message.str();
      EXPECT_NE(nacl_arm_val::kReportProblemSafety, first.method())
          << "Store should not be unsafe even though guard is bogus: "
          << message.str();
      EXPECT_EQ(nacl_arm_val::kProblemUnsafeLoadStore, first.problem())
          << message;
    }
  }
}

TEST_F(ValidatorTests, ValidMasksOnUnsafeStores) {
  static const AnnotatedInstruction invalid_stores[] = {
    { 0x07810002, "str r0, [r1, r2]: register-plus-register addressing" },
    { 0x07010002, "str r0, [r1, -r2]: register-minus-register addressing" },
    { 0x07810182, "str r0, [r1, r2, LSL #3]: complicated addressing 1" },
    { 0x07018482, "str r0, [r1, -r2, ASR #16]: complicated addressing 2" },
  };

  for (unsigned p = 0; p < 15; p++) {
    // Conditionally executed instructions have a top nibble of 0..14.
    // 15 is an escape sequence used to fit in additional encodings.
    arm_inst predicate = p << 28;

    for (unsigned m = 0; m < NACL_ARRAY_SIZE(examples_of_safe_masks); m++) {
      for (unsigned s = 0; s < NACL_ARRAY_SIZE(invalid_stores); s++) {
        ostringstream message;
        message << examples_of_safe_masks[m].about
                << ", "
                << invalid_stores[s].about
                << " (predicate #" << p << ")";
        arm_inst program[] = {
          examples_of_safe_masks[m].inst | predicate,
          invalid_stores[s].inst | predicate,
        };

        vector<ProblemRecord> problems =
            validation_should_fail(program,
                                   NACL_ARRAY_SIZE(program),
                                   kDefaultBaseAddr,
                                   message.str());

        // EXPECT/continue rather than ASSERT so that we run the other cases.
        EXPECT_EQ(1U, problems.size());
        if (problems.size() != 1) continue;

        ProblemRecord first = problems[0];
        EXPECT_EQ(kDefaultBaseAddr + 4, first.vaddr())
            << "Problem report must point to the store: "
            << message.str();
        EXPECT_EQ(nacl_arm_val::kReportProblemSafety, first.method())
            << "Store must be flagged by the decoder as unsafe: "
            << message.str();
        EXPECT_EQ(nacl_arm_val::kProblemUnsafe, first.problem())
            << message;
      }
    }
  }
}

TEST_F(ValidatorTests, ScaryUndefinedInstructions) {
  // These instructions are undefined today (ARMv7-A) but may become defined
  // tomorrow.  We ban them since we can't reason about their side effects.
  static const AnnotatedInstruction undefined_insts[] = {
    { 0xE05DEA9D, "An undefined instruction in the multiply space" },
  };
  for (unsigned i = 0; i < NACL_ARRAY_SIZE(undefined_insts); i++) {
    arm_inst program[] = { undefined_insts[i].inst };

    vector<ProblemRecord> problems =
        validation_should_fail(program,
                               NACL_ARRAY_SIZE(program),
                               kDefaultBaseAddr,
                               undefined_insts[i].about);

    // EXPECT/continue rather than ASSERT so that we run the other cases.
    EXPECT_EQ(1U, problems.size());
    if (problems.size() != 1) continue;

    ProblemSpy spy;
    ProblemRecord first = problems[0];
    EXPECT_EQ(kDefaultBaseAddr, first.vaddr())
        << "Problem report must point to the only instruction: "
        << undefined_insts[i].about;
    EXPECT_EQ(nacl_arm_val::kReportProblemSafety, first.method())
        << "Store must be flagged by the decoder as unsafe: "
        << undefined_insts[i].about;
    EXPECT_EQ(nacl_arm_dec::UNDEFINED, spy.GetSafetyLevel(first))
        << "Instruction must be flagged as UNDEFINED: "
        << undefined_insts[i].about;
    EXPECT_EQ(nacl_arm_val::kProblemUnsafe, first.problem())
        << "Instruction must be marked unsafe: "
        << undefined_insts[i].about;
  }
}

TEST_F(ValidatorTests, LessScaryUndefinedInstructions) {
  // These instructions are specified by ARM as *permanently* undefined, so we
  // treat them as a reliable Illegal Instruction trap.

  static const AnnotatedInstruction perm_undefined[] = {
    { 0xE7FFDEFE, "permanently undefined instruction produced by LLVM" },
  };

  for (unsigned i = 0; i < NACL_ARRAY_SIZE(perm_undefined); i++) {
    arm_inst program[] = { perm_undefined[i].inst };
    validation_should_pass(program,
                           1,
                           kDefaultBaseAddr,
                           perm_undefined[i].about);
  }
}

TEST_F(ValidatorTests, PcRelativeFirstInst) {
  // Note: This tests the fix for issue 2771.
  static const arm_inst pcrel_boundary_tests[] = {
    0xe59f0000,  // ldr     r0, [pc, #0]
    0xe320f000,  // nop     {0}
    0xe320f000,  // nop     {0}
    0xe320f000,  // nop     {0}"
  };
  validation_should_pass(pcrel_boundary_tests,
                         NACL_ARRAY_SIZE(pcrel_boundary_tests),
                         kDefaultBaseAddr,
                         "pc relative first instruction in first bundle");
}

TEST_F(ValidatorTests, PcRelativeFirst2ndBundle) {
  // Note: This tests the fix for issue 2771.
  static const arm_inst pcrel_boundary_tests[] = {
    0xe320f000,  // nop     {0}
    0xe320f000,  // nop     {0}
    0xe320f000,  // nop     {0}
    0xe320f000,  // nop     {0}
    0xe59f0000,  // ldr     r0, [pc, #0]
  };
  validation_should_pass(pcrel_boundary_tests,
                         NACL_ARRAY_SIZE(pcrel_boundary_tests),
                         kDefaultBaseAddr,
                         "pc relative first instruction in 2nd bundle");
}

TEST_F(ValidatorTests, SafeConditionalBicLdrTest) {
  // Test if we fixed bug with conditional Bic Loads (issue 2769).
  static const arm_inst bic_ldr_safe_test[] = {
    0x03c22103,  // biceq   r2, r2, #-1073741824    ; 0xc0000000
    0x01920f9f,  // ldrexeq r0, [r2]
  };
  validation_should_pass(bic_ldr_safe_test,
                         NACL_ARRAY_SIZE(bic_ldr_safe_test),
                         kDefaultBaseAddr,
                         "Safe conditional bic ldr test");
}

TEST_F(ValidatorTests, ConditionalBicsLdrTest) {
  // Test if we fail because Bic updates the flags register, making
  // the conditional Bic load incorrect (issue 2769).
  static const arm_inst bics_ldr_unsafe_test[] = {
    0x03d22103,  // bicseq  r2, r2, #-1073741824    ; 0xc0000000
    0x01920f9f,  // ldrexeq r0, [r2]
  };
  vector<ProblemRecord> problems =
      validation_should_fail(bics_ldr_unsafe_test,
                             NACL_ARRAY_SIZE(bics_ldr_unsafe_test),
                             kDefaultBaseAddr,
                             "Conditional bics ldr test");
  EXPECT_EQ(1U, problems.size());
  if (problems.size() == 0) return;

  ProblemSpy spy;
  ProblemRecord problem = problems[0];
  EXPECT_EQ(kDefaultBaseAddr + 4, problem.vaddr())
      << "Problem report should point to the ldr instruction.";
  EXPECT_NE(nacl_arm_val::kReportProblemSafety, problem.method());
  EXPECT_EQ(nacl_arm_dec::MAY_BE_SAFE, spy.GetSafetyLevel(problem));
  EXPECT_EQ(nacl_arm_val::kProblemUnsafeLoadStore, problem.problem());
}

TEST_F(ValidatorTests, DifferentConditionsBicLdrTest) {
  // Test if we fail because the Bic and Ldr instructions have
  // different conditional flags.
  static const arm_inst bic_ldr_diff_conds[] = {
    0x03c22103,  // biceq   r2, r2, #-1073741824    ; 0xc0000000
    0xc1920f9f,  // ldrexgt r0, [r2]
  };
  vector<ProblemRecord> problems=
      validation_should_fail(bic_ldr_diff_conds,
                             NACL_ARRAY_SIZE(bic_ldr_diff_conds),
                             kDefaultBaseAddr,
                             "Different conditions bic ldr test");
  EXPECT_EQ(1U, problems.size());
  if (problems.size() == 0) return;

  ProblemSpy spy;
  ProblemRecord problem = problems[0];
  EXPECT_EQ(kDefaultBaseAddr + 4, problem.vaddr())
      << "Problem report should point to the ldr instruction.";
  EXPECT_NE(nacl_arm_val::kReportProblemSafety, problem.method());
  EXPECT_EQ(nacl_arm_dec::MAY_BE_SAFE, spy.GetSafetyLevel(problem));
  EXPECT_EQ(nacl_arm_val::kProblemUnsafeLoadStore, problem.problem());
}

TEST_F(ValidatorTests, BfcLdrInstGoodTest) {
  // Test if we can use bfc to clear mask bits.
  static const arm_inst bfc_inst[] = {
    0xe7df2f1f,  // bfc r2, #30, #2
    0xe1920f9f,  // ldrex r0, [r2]
  };
  validation_should_pass(bfc_inst,
                         NACL_ARRAY_SIZE(bfc_inst),
                         kDefaultBaseAddr,
                         "Bfc Lcr instruction mask good test");
}

TEST_F(ValidatorTests, BfcLdrInstMaskTooBigTest) {
  // Run test where bfc mask is too big (acceptable to mask off more than
  // needed).
  static const arm_inst bfc_inst[] = {
    0xe7df2e9f,  // bfc r2, #29, #3
    0xe1920f9f,  // ldrex r0, [r2]
  };
  validation_should_pass(bfc_inst,
                         NACL_ARRAY_SIZE(bfc_inst),
                         kDefaultBaseAddr,
                         "Bfc Ldr instruction mask too big test");
}

TEST_F(ValidatorTests, BfcLdrInstMaskWrongPlaceTest) {
  // Run test where bfc mask is in the wrong place.
  static const arm_inst bfc_inst[] = {
    0xe7da2c9f,  // bfc r2, #25, #2
    0xe1920f9f,  // ldrex r0, [r2]
  };
  validation_should_fail(bfc_inst,
                         NACL_ARRAY_SIZE(bfc_inst),
                         kDefaultBaseAddr,
                         "Bfc Ldr instruction mask wrong place test");
}

struct AlwaysDominatesTestInfo {
  arm_inst inst[2];
  const char* name[2];
  bool first_inst_can_set_flags;
};
TEST_F(ValidatorTests, AlwaysDominatesTest) {
  // Test always_dominates, with all conditional combinations of:
  AlwaysDominatesTestInfo test[2] = {
    { {
        // BFC followed by a load/store.
        0xe7df2f1f,  // bfcCC r2, #30, #2
        0xe1920f9f,  // ldrexCC r0, [r2]
      }, { "bfc", "ldrex" }, false },
    { {
        // BIC (potentially setting flags) followed by a branch.
        0xe3cee2fe,  // bic[s]CC lr, lr, #-536870897     ; 0xe000000f
        0xe12fff1e,  // bxCC lr
      }, { "bic", "bx" }, true },
  };

  for (AlwaysDominatesTestInfo* t = &test[0];
       t != &test[NACL_ARRAY_SIZE(test)];
       ++t) {
    for (int s = 0; s < (t->first_inst_can_set_flags ? 2 : 1); ++s) {
      if (t->first_inst_can_set_flags) {
        t->inst[0] = SetSBit(t->inst[0], s);
      }

      Instruction::Condition cond[2];
      for (cond[0] = Instruction::EQ;
           cond[0] <= Instruction::AL;
           cond[0] = Instruction::Next(cond[0])) {
        for (cond[1] = Instruction::EQ;
             cond[1] <= Instruction::AL;
             cond[1] = Instruction::Next(cond[1])) {
          t->inst[0] = ChangeCond(t->inst[0], cond[0]);
          t->inst[1] = ChangeCond(t->inst[1], cond[1]);

          std::string name0(std::string(t->name[0]) + (s ? "s" : "") +
                            Instruction::ToString(cond[0]));
          std::string name1(std::string(t->name[1]) +
                            Instruction::ToString(cond[1]));
          ostringstream message;
          message << name0 <<
              " (0x" << std::hex << std::setfill('0') << std::setw(8) <<
              static_cast<uint32_t>(t->inst[0]) <<
              std::resetiosflags(std::ios_base::showbase) << ") "
              "with a correct mask, followed by " << name1 <<
              " (0x" << std::hex << std::setfill('0') << std::setw(8) <<
              static_cast<uint32_t>(t->inst[1]) <<
              std::resetiosflags(std::ios_base::showbase) << "): ";

          if (s) {
            validation_should_fail(t->inst, NACL_ARRAY_SIZE(t->inst),
                                   kDefaultBaseAddr,
                                   message.str() + name0 + " sets flags "
                                   "when it's only supposed to enforce SFI on "
                                   "the subsequent " + name1 + ", we "
                                   "could allow this but it makes the "
                                   "validator's code more complex and it's "
                                   "harder to reason about back-to-back "
                                   "conditional instructions with "
                                   "intervening flag setting (especially with "
                                   "ARM's partial NZCV flag setting).");
          } else if (cond[0] == Instruction::AL) {
            validation_should_pass(t->inst, NACL_ARRAY_SIZE(t->inst),
                                   kDefaultBaseAddr,
                                   message.str() + "an unconditional " +
                                   name0 + " always dominates the "
                                   "subsequent " + name1 +
                                   " instruction.");
          } else if (cond[1] == Instruction::AL) {
            EXPECT_NE(cond[0], Instruction::AL);
            validation_should_fail(t->inst, NACL_ARRAY_SIZE(t->inst),
                                   kDefaultBaseAddr,
                                   message.str() + name0 + " is "
                                   "conditional, but the subsequent " +
                                   name1 + " isn't.");
          } else if ((cond[1] == cond[0]) ||
                   (cond[1] == Instruction::EQ && cond[0] == Instruction::LS) ||
                   (cond[1] == Instruction::CC && cond[0] == Instruction::LS) ||
                   (cond[1] == Instruction::HI && cond[0] == Instruction::NE) ||
                   (cond[1] == Instruction::HI && cond[0] == Instruction::CS) ||
                   (cond[1] == Instruction::GT && cond[0] == Instruction::NE) ||
                   (cond[1] == Instruction::GT && cond[0] == Instruction::GE) ||
                   (cond[1] == Instruction::LE && cond[0] == Instruction::EQ) ||
                   (cond[1] == Instruction::LE && cond[0] == Instruction::LS) ||
                   (cond[1] == Instruction::LE && cond[0] == Instruction::LT)) {
            validation_should_pass(t->inst, NACL_ARRAY_SIZE(t->inst),
                                   kDefaultBaseAddr,
                                   message.str() + name1 + "'s "
                                   "condition being true necessarily implies "
                                   "that " + name0 + "'s condition was "
                                   "also true.");
          } else {
            validation_should_fail(t->inst, NACL_ARRAY_SIZE(t->inst),
                                   kDefaultBaseAddr,
                                   message.str() + name1 + "'s condition "
                                   "being true doesn't necessarily imply "
                                   "that " + name0 + "'s condition was "
                                   "also true, err on the side of caution and "
                                   "disallow.");
          }
        }
      }
    }
  }
}

// TODO(karl): Add pattern rules and test cases for using bfc to update SP.

TEST_F(ValidatorTests, AddConstToSpTest) {
  // Show that we can add a constant to the stack pointer is fine,
  // so long as we follow it with a mask instruction.
  static const arm_inst sp_inst[] = {
    0xe28dd00c,  // add sp, sp, #12
    0xe3cdd2ff,  // bic     sp, sp, #-268435441     ; 0xf000000f
  };
  validation_should_pass(sp_inst,
                         NACL_ARRAY_SIZE(sp_inst),
                         kDefaultBaseAddr,
                         "Add constant (12) to sp, then mask with bic");
}

TEST_F(ValidatorTests, AddConstToSpBicTestDoesFollows) {
  // Run test where we conditionally add a constant to a stack pointer,
  // followed by a mask.
  // Note: Implicitly tests always_postdominates.
  for (int cond = Instruction::EQ; cond < Instruction::AL; ++cond) {
    arm_inst inst[] = {
      0x028dd00c,  // addeq sp, sp, #12
      0xe3cdd2ff,  // bic sp, sp, #-268435441     ; 0xf000000f
    };
    inst[0] = ChangeCond(inst[0], static_cast<Instruction::Condition>(cond));
    validation_should_pass(inst,
                           NACL_ARRAY_SIZE(inst),
                           kDefaultBaseAddr,
                           "Add constant (12) to sp, then mask with bic, "
                           "tests always_postdominates succeeds");
  }
}

TEST_F(ValidatorTests, AddConstToSpBicTestDoesntFollows) {
  // Run test where we add a constant to a stack pointer, followed
  // by a conditional mask.
  // Note: Implicitly tests always_postdominates.
  for (int cond = Instruction::EQ; cond < Instruction::AL; ++cond) {
    arm_inst inst[] = {
      0xe28dd00c,  // add sp, sp, #12
      0x03cdd2ff,  // biceq sp, sp, #-268435441   ; 0xf000000f
    };
    inst[1] = ChangeCond(inst[1], static_cast<Instruction::Condition>(cond));
    validation_should_fail(inst,
                           NACL_ARRAY_SIZE(inst),
                           kDefaultBaseAddr,
                           "Add constant (12) to sp, then mask with bic, "
                           "tests always_postdominates fails");
  }
}

TEST_F(ValidatorTests, CheckVectorLoadPcRelative) {
  // Run test where we do a vector load using a pc relative address.
  // Corresponds to issue 2906.
  static const arm_inst load_inst[] = {
    0xed9f0b04,  // vldr        d0, [pc, #16]
  };
  validation_should_pass(load_inst,
                         NACL_ARRAY_SIZE(load_inst),
                         kDefaultBaseAddr,
                         "Load vector register using pc relative address");
}

TEST_F(ValidatorTests, CheckPushSpUnpredictable) {
  // Run test to verify that "Push {sp}", encoding A2 on a8-248 of ARM manual,
  // is unpredictable (i.e. unsafe).
  all_cond_values_fail(0xe52dd004,  // push {sp}
                       kDefaultBaseAddr,
                       "push {sp} (A2 a8-248) should be unpredictable");
}

TEST_F(ValidatorTests, CheckPushPcUnpredictable) {
  // Run test to verify that "Push {pc}", encoding A2 on a8-248 of ARM manual,
  // is unsafe.
  all_cond_values_fail(0xe52dF004,  // push {pc}
                       kDefaultBaseAddr,
                       "push {pc} (A2 A8-248) should be unpredictable");
}

};  // anonymous namespace

// Test driver function.
int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}