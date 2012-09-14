/*
 * Copyright (c) 2012 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <inttypes.h>

#include "native_client/src/trusted/service_runtime/nacl_config.h"
#include "native_client/src/trusted/validator_arm/model.h"
#include "native_client/src/trusted/validator_arm/validator.h"
#include "native_client/src/include/nacl_macros.h"
#include "native_client/src/include/portability_bits.h"
#include "native_client/src/shared/platform/nacl_log.h"

using nacl_arm_dec::Instruction;
using nacl_arm_dec::ClassDecoder;
using nacl_arm_dec::Register;
using nacl_arm_dec::RegisterList;
using nacl_arm_dec::kRegisterNone;
using nacl_arm_dec::kConditions;
using nacl_arm_dec::kRegisterPc;
using nacl_arm_dec::kRegisterLink;

using std::vector;

namespace nacl_arm_val {

// Note: When updating the code on ProblemSink, be sure to update
// file problem_reporter.cc appropriately. Both files must maintain
// user_data consistently for the code to work.

static const size_t kUserDataSize[] = {
  1,  // kReportProblemSafety,
  0,  // kReportProblem,
  1,  // kReportProblemAddress,
  5,  // kReportProblemInstructionPair,
  1,  // kReportProblemRegister,
  6,  // kReportProblemRegisterInstructionPair,
  1,  // kReportProblemRegisterList,
  6,  // kReportProblemRegisterListInstructionPair
};

size_t ProblemSink::UserDataSize(ValidatorProblemMethod method) {
  size_t index = static_cast<size_t>(method);
  return (index < NACL_ARRAY_SIZE(kUserDataSize)) ? kUserDataSize[index] : 0;
}

void ProblemSink::ReportProblemInternal(uint32_t vaddr,
                                        ValidatorProblem problem,
                                        ValidatorProblemMethod method,
                                        ValidatorProblemUserData user_data) {
  UNREFERENCED_PARAMETER(vaddr);
  UNREFERENCED_PARAMETER(problem);
  UNREFERENCED_PARAMETER(method);
  UNREFERENCED_PARAMETER(user_data);

  // Before returning, be sure unused fields in user data are set to zero.
  // This way, we don't need to fill in each ReportProblem... method.
  for (size_t i = UserDataSize(method);
       i < kValidatorProblemUserDataSize; ++i) {
    user_data[i] = 0;
  };
}

void ProblemSink::ReportProblemSafety(
    uint32_t vaddr, nacl_arm_dec::SafetyLevel safety) {
  ValidatorProblemUserData user_data = {
    static_cast<uint32_t>(safety),
  };
  NACL_COMPILE_TIME_ASSERT(NACL_ARRAY_SIZE(user_data) <=
                           kValidatorProblemUserDataSize);
  ReportProblemInternal(vaddr, kProblemUnsafe,
                        kReportProblemSafety, user_data);;
}

void ProblemSink::ReportProblem(uint32_t vaddr, ValidatorProblem problem) {
  ValidatorProblemUserData user_data = {
  };
  NACL_COMPILE_TIME_ASSERT(NACL_ARRAY_SIZE(user_data) <=
                           kValidatorProblemUserDataSize);
  ReportProblemInternal(vaddr, problem, kReportProblem, user_data);
}

void ProblemSink::ReportProblemAddress(
    uint32_t vaddr, ValidatorProblem problem, uint32_t problem_vaddr) {
  ValidatorProblemUserData user_data = {
    problem_vaddr
  };
  NACL_COMPILE_TIME_ASSERT(NACL_ARRAY_SIZE(user_data) <=
                           kValidatorProblemUserDataSize);
  ReportProblemInternal(vaddr, problem, kReportProblemAddress, user_data);
}

void ProblemSink::ReportProblemInstructionPair(
    uint32_t vaddr, ValidatorProblem problem,
    ValidatorInstructionPairProblem pair_problem,
    const DecodedInstruction& first, const DecodedInstruction& second) {
  ValidatorProblemUserData user_data = {
    static_cast<uint32_t>(pair_problem),
    first.addr(),
    first.inst().Bits(),
    second.addr(),
    second.inst().Bits()
  };
  NACL_COMPILE_TIME_ASSERT(NACL_ARRAY_SIZE(user_data) <=
                           kValidatorProblemUserDataSize);
  ReportProblemInternal(vaddr, problem,
                        kReportProblemInstructionPair, user_data);
}

void ProblemSink::ReportProblemRegister(
    uint32_t vaddr, ValidatorProblem problem,
    nacl_arm_dec::Register reg) {
  ValidatorProblemUserData user_data = {
    reg.number()
  };
  NACL_COMPILE_TIME_ASSERT(NACL_ARRAY_SIZE(user_data) <=
                           kValidatorProblemUserDataSize);
  ReportProblemInternal(vaddr, problem, kReportProblemRegister, user_data);
}

void ProblemSink::ReportProblemRegisterInstructionPair(
    uint32_t vaddr, ValidatorProblem problem,
    ValidatorInstructionPairProblem pair_problem,
    nacl_arm_dec::Register reg,
    const DecodedInstruction& first, const DecodedInstruction& second) {
  ValidatorProblemUserData user_data = {
    static_cast<uint32_t>(pair_problem),
    reg.number(),
    first.addr(),
    first.inst().Bits(),
    second.addr(),
    second.inst().Bits()
  };
  NACL_COMPILE_TIME_ASSERT(NACL_ARRAY_SIZE(user_data) <=
                           kValidatorProblemUserDataSize);
  ReportProblemInternal(vaddr, problem,
                        kReportProblemRegisterInstructionPair, user_data);
}

void ProblemSink::ReportProblemRegisterList(
    uint32_t vaddr, ValidatorProblem problem,
    nacl_arm_dec::RegisterList registers) {
  ValidatorProblemUserData user_data = {
    registers.bits()
  };
  NACL_COMPILE_TIME_ASSERT(NACL_ARRAY_SIZE(user_data) <=
                           kValidatorProblemUserDataSize);
  ReportProblemInternal(vaddr, problem,
                        kReportProblemRegisterList, user_data);
}

void ProblemSink::ReportProblemRegisterListInstructionPair(
    uint32_t vaddr, ValidatorProblem problem,
    ValidatorInstructionPairProblem pair_problem,
    nacl_arm_dec::RegisterList registers,
    const DecodedInstruction& first, const DecodedInstruction& second) {
  ValidatorProblemUserData user_data = {
    static_cast<uint32_t>(pair_problem),
    registers.bits(),
    first.addr(),
    first.inst().Bits(),
    second.addr(),
    second.inst().Bits()
  };
  NACL_COMPILE_TIME_ASSERT(NACL_ARRAY_SIZE(user_data) <=
                           kValidatorProblemUserDataSize);
  ReportProblemInternal(vaddr, problem,
                        kReportProblemRegisterListInstructionPair, user_data);
}

/*********************************************************
 * Implementations of patterns used in the first pass.
 *
 * N.B.  IF YOU ADD A PATTERN HERE, REGISTER IT BELOW.
 * See the list in apply_patterns.
 *********************************************************/

// A possible result from a validator pattern.
enum PatternMatch {
  // The pattern does not apply to the instructions it was given.
  NO_MATCH,
  // The pattern matches and is safe.
  PATTERN_SAFE,
  // The pattern matches, and has detected a problem.
  PATTERN_UNSAFE
};

// Models data collected when matching a pair of instructions to a validator
// pattern.
class InstructionPairMatchData {
 public:
  explicit InstructionPairMatchData(ProblemSink* out)
      : out_(out),
        match_(PATTERN_UNSAFE),
        problem_(kValidatorProblemSize),
        pair_problem_(kNoSpecificPairProblem),
        first_is_basis_(false),
        is_single_instruction_pattern_(false)
  {}

  // Defines the problem sink to report problems to.
  ProblemSink* out_;

  // Defines how successful the validator was on matching the given pattern.
  PatternMatch match_;

  // Defines the validator problem that the pattern is trying to check.
  ValidatorProblem problem_;

  // Defines any validator problems due to conditions that cross instruction
  // boundaries.
  ValidatorInstructionPairProblem pair_problem_;

  // If set, assume the problem is in the first instruction (rather than the
  // second).
  bool first_is_basis_;

  // If true, the pattern is for one instruction (defined by first_is_basis)
  // instead of two.
  bool is_single_instruction_pattern_;
};

// Looks at the conditions associated with a pair of instructions
// associated with a validator pattern, and determines what problems
// the conditions may have played in not allowing the instruction
// pair to be atomic.
// Parameters:
//    first: The first instruction in the pair wrt the direction being
//        tested (not the order the instructions appear).
//    second: The second instruction in the pair wrt to the direction
//        being tested. Hence, we check if the conditions of the first
//        instruction implies the conditions of the second.
static ValidatorInstructionPairProblem GetPairConditionProblem(
    const DecodedInstruction& first,
    const DecodedInstruction& second) {
  UNREFERENCED_PARAMETER(second);
  if (first.defines(nacl_arm_dec::kCondsDontCareFlag)) {
    return kFirstNotAllowsInInstructionPairs;
  } else if (first.defines(kConditions)) {
    return kFirstSetsConditionFlags;
  } else {
    return kConditionsOnPairNotSafe;
  }
}

// Ensures that all loads/stores use a safe base address.  A base address is
// safe if it
//     1. Has specific bits masked off by its immediate predecessor, or
//     2. Is predicated on those bits being clear, as tested by its immediate
//        predecessor, or
//     3. Is in a register defined as always containing a safe address.
//
// This pattern concerns itself with case #1, early-exiting if it finds #2.
static void check_loadstore_mask(
    const SfiValidator& sfi,
    const DecodedInstruction& first,
    const DecodedInstruction& second,
    InstructionPairMatchData* match_data) {
  match_data->problem_ = kProblemUnsafeLoadStore;
  if (second.base_address_register().
      Equals(kRegisterNone) /* not a load/store */
      || sfi.is_data_address_register(second.base_address_register())) {
    match_data->match_ = NO_MATCH;
    return;
  }

  if (second.base_address_register().Equals(kRegisterPc)
      && second.offset_is_immediate()) {
    // PC + immediate addressing is always safe.
    match_data->match_ = PATTERN_SAFE;
    match_data->is_single_instruction_pattern_ = true;
    return;
  }

  if (first.defines(second.base_address_register())
      && first.clears_bits(sfi.data_address_mask())
      && first.always_dominates(second)) {
    match_data->match_ = PATTERN_SAFE;
    return;
  }

  if (first.sets_Z_if_bits_clear(second.base_address_register(),
                                 sfi.data_address_mask())
      && second.is_eq_conditional_on(first)) {
    match_data->match_ = PATTERN_SAFE;
    return;
  }

  // If reached, there is a problem!
  // Try to best categorize the problem and report.
  if (first.defines(second.base_address_register())) {
    if (first.clears_bits(sfi.data_address_mask())) {
      match_data->out_->ReportProblemRegisterInstructionPair(
          second.addr(),
          kProblemUnsafeLoadStore,
          GetPairConditionProblem(first, second),
          second.base_address_register(),
          first, second);
    } else {
      match_data->out_->ReportProblemRegister(
          second.addr(),
          kProblemUnsafeLoadStore,
          second.base_address_register());
    }
  } else if (first.sets_Z_if_bits_clear(second.base_address_register(),
                                        sfi.data_address_mask())) {
    match_data->out_->ReportProblemRegisterInstructionPair(
        second.addr(),
        kProblemUnsafeLoadStore,
        kEqConditionalOn,
        second.base_address_register(), first, second);
  } else if (second.base_address_register().Equals(kRegisterPc)) {
    match_data->out_->ReportProblem(second.addr(), kProblemIllegalPcLoadStore);
  } else {
    match_data->out_->ReportProblemRegister(second.addr(),
                                            kProblemUnsafeLoadStore,
                                            second.base_address_register());
  }
  return;
}

// Ensures that all indirect branches use a safe destination address.  A
// destination address is safe if it has specific bits masked off by its
// immediate predecessor.
static void check_branch_mask(
    const SfiValidator& sfi,
    const DecodedInstruction& first,
    const DecodedInstruction& second,
    InstructionPairMatchData* match_data) {
  match_data->problem_ = kProblemUnsafeBranch;
  if (second.branch_target_register().Equals(kRegisterNone)) {
    match_data->match_ = NO_MATCH;
    return;
  }

  if (first.defines(second.branch_target_register())
      && first.clears_bits(sfi.code_address_mask())
      && first.always_dominates(second)) {
    match_data->match_ = PATTERN_SAFE;
    return;
  }

  // If reached, there is a problem!
  // Try to better diagnose the problem being reported.
  if (first.defines(second.branch_target_register())) {
    if (first.clears_bits(sfi.code_address_mask())) {
      match_data->out_->ReportProblemRegisterInstructionPair(
          second.addr(),
          kProblemUnsafeBranch,
          GetPairConditionProblem(first, second),
          second.branch_target_register(), first, second);
    } else {
      match_data->out_->ReportProblemRegister(
          second.addr(), kProblemUnsafeBranch, second.branch_target_register());
    }
  } else {
    match_data->out_->ReportProblemRegister(second.addr(), kProblemUnsafeBranch,
                                            second.branch_target_register());
  }
  return;
}

// Verifies that any instructions that update a data-address register are
// immediately followed by a mask.
static void check_data_register_update(
    const SfiValidator& sfi,
    const DecodedInstruction& first,
    const DecodedInstruction& second,
    InstructionPairMatchData* match_data) {
  match_data->problem_ = kProblemUnsafeDataWrite;
  match_data->first_is_basis_ = true;
  if (!first.defines_any(sfi.data_address_registers())) {
    match_data->match_ = NO_MATCH;
    return;
  }

  // A single safe data register update doesn't affect control flow.
  if (first.clears_bits(sfi.data_address_mask())) {
    match_data->match_ = NO_MATCH;
    return;
  }

  // Exempt updates due to writeback
  RegisterList data_addr_defs(first.defs().
                              Intersect(sfi.data_address_registers()));

  if (first.immediate_addressing_defs().
      Intersect(sfi.data_address_registers()).Equals(data_addr_defs)) {
    match_data->match_ = NO_MATCH;
    return;
  }

  if (second.defines_all(data_addr_defs)
      && second.clears_bits(sfi.data_address_mask())
      && second.always_postdominates(first)) {
    match_data->match_ = PATTERN_SAFE;
    return;
  }

  // If reached, there is a problem!
  // Try to better diagnose the problem being reported.
  if (second.defines_all(data_addr_defs) &&
      second.clears_bits(sfi.data_address_mask())) {
    match_data->out_->ReportProblemRegisterListInstructionPair(
        first.addr(),
        kProblemUnsafeDataWrite,
        GetPairConditionProblem(first, second),
        data_addr_defs, first, second);
  } else {
    match_data->out_->ReportProblemRegisterList(first.addr(),
                                                kProblemUnsafeDataWrite,
                                                data_addr_defs);
  }
  return;
}

// Checks the location of linking branches -- to be useful, they must be in
// the last bundle slot.
//
// This is not a security check per se, more of a guard against Stupid Compiler
// Tricks.
static PatternMatch check_call_position(const SfiValidator& sfi,
                                        const DecodedInstruction& inst,
                                        ProblemSink* out) {
  // Identify linking branches through their definitions:
  if (inst.defines_all(RegisterList(kRegisterPc).Add(kRegisterLink))) {
    uint32_t last_slot = sfi.bundle_for_address(inst.addr()).end_addr() - 4;
    if (inst.addr() != last_slot) {
      out->ReportProblem(inst.addr(), kProblemMisalignedCall);
      return PATTERN_UNSAFE;
    }
  }
  return NO_MATCH;
}

// Checks for instructions that alter any read-only register.
static PatternMatch check_read_only(const SfiValidator& sfi,
                                    const DecodedInstruction& inst,
                                    ProblemSink* out) {
  if (inst.defines_any(sfi.read_only_registers())) {
    out->ReportProblemRegisterList(
        inst.addr(), kProblemReadOnlyRegister,
        inst.defs().Intersect(sfi.read_only_registers()));
    return PATTERN_UNSAFE;
  }
  return NO_MATCH;
}

// Checks writes to r15 from instructions that aren't branches.
static PatternMatch check_pc_writes(const SfiValidator& sfi,
                                    const DecodedInstruction& inst,
                                    ProblemSink* out) {
  if (inst.is_relative_branch()
      || !inst.branch_target_register().Equals(kRegisterNone)) {
    // It's a branch.
    return NO_MATCH;
  }

  if (!inst.defines(nacl_arm_dec::kRegisterPc))
    return NO_MATCH;

  if (inst.clears_bits(sfi.code_address_mask())) {
    return PATTERN_SAFE;
  } else {
    out->ReportProblemRegister(inst.addr(), kProblemUnsafeBranch, kRegisterPc);
    return PATTERN_UNSAFE;
  }
}

/*********************************************************
 *
 * Implementation of SfiValidator itself.
 *
 *********************************************************/

// Flags are:
//    N - Negative condition code flag.
//    Z - Zero condition code flag.
//    C - Carry condition code flag.
//    V - Overflow condition code flag.
const bool SfiValidator::
condition_implies[nacl_arm_dec::Instruction::kConditionSize + 1]
                 [nacl_arm_dec::Instruction::kConditionSize + 1] = {
# if defined(T) || defined(_)
#   error Macros already defined.
# endif
# define T true
# define _ false
  //                       EQ NE CS CC MI PL VS VC HI LS GE LT GT LE AL UN
  /* EQ => Z==1        */ { T, _, _, _, _, _, _, _, _, T, _, _, _, _, T, T },
  /* NE => Z==0        */ { _, T, _, _, _, _, _, _, _, _, _, _, _, _, T, T },
  /* CS => C==1        */ { _, _, T, _, _, _, _, _, _, _, _, _, _, _, T, T },
  /* CC => C==0        */ { _, _, _, T, _, _, _, _, _, T, _, _, _, _, T, T },
  /* MI => N==1        */ { _, _, _, _, T, _, _, _, _, _, _, _, _, _, T, T },
  /* PL => N==0        */ { _, _, _, _, _, T, _, _, _, _, _, _, _, _, T, T },
  /* VS => V==1        */ { _, _, _, _, _, _, T, _, _, _, _, _, _, _, T, T },
  /* VC => V==0        */ { _, _, _, _, _, _, _, T, _, _, _, _, _, _, T, T },
  /* HI => C==1 & Z==0 */ { _, T, T, _, _, _, _, _, T, _, _, _, _, _, T, T },
  /* LS => C==0 | Z==1 */ { _, _, _, _, _, _, _, _, _, T, _, _, _, _, T, T },
  /* GE => N==V        */ { _, _, _, _, _, _, _, _, _, _, T, _, _, _, T, T },
  /* LT => N!=V        */ { _, _, _, _, _, _, _, _, _, _, _, T, _, _, T, T },
  /* GT => Z==0 & N==V */ { _, T, _, _, _, _, _, _, _, _, T, _, T, _, T, T },
  /* LE => Z==1 & N!=V */ { T, _, _, _, _, _, _, _, _, T, _, T, _, T, T, T },
  /* AL => Any         */ { _, _, _, _, _, _, _, _, _, _, _, _, _, _, T, T },
  /* UN => Any         */ { _, _, _, _, _, _, _, _, _, _, _, _, _, _, T, T },
# undef _
# undef T
};

SfiValidator::SfiValidator(uint32_t bytes_per_bundle,
                           uint32_t code_region_bytes,
                           uint32_t data_region_bytes,
                           RegisterList read_only_registers,
                           RegisterList data_address_registers)
    : bytes_per_bundle_(bytes_per_bundle),
      code_region_bytes_(code_region_bytes),
      data_region_bytes_(data_region_bytes),
      read_only_registers_(read_only_registers),
      data_address_registers_(data_address_registers),
      decode_state_(),
      construction_failed_(false) {
  // Make sure we can construct sane masks with the values.
  if ((nacl::PopCount(bytes_per_bundle_) != 1) ||
      (nacl::PopCount(code_region_bytes_) != 1) ||
      (nacl::PopCount(data_region_bytes_) != 1) ||
      (bytes_per_bundle_ < 2) ||
      (code_region_bytes_ < 2) ||
      (data_region_bytes_ < 2) ||
      (code_region_bytes_ < bytes_per_bundle_)) {
    construction_failed_ = true;
  }
}

SfiValidator::SfiValidator(const SfiValidator& v)
    : bytes_per_bundle_(v.bytes_per_bundle_),
      code_region_bytes_(v.code_region_bytes_),
      data_region_bytes_(v.data_region_bytes_),
      read_only_registers_(v.read_only_registers_),
      data_address_registers_(v.data_address_registers_),
      decode_state_(),
      construction_failed_(v.construction_failed_) {}

SfiValidator& SfiValidator::operator=(const SfiValidator& v) {
  bytes_per_bundle_ = v.bytes_per_bundle_;
  code_region_bytes_ = v.code_region_bytes_;
  data_region_bytes_ = v.data_region_bytes_;
  read_only_registers_.Copy(v.read_only_registers_);
  data_address_registers_.Copy(v.data_address_registers_);
  construction_failed_ = v.construction_failed_;
  return *this;
}

bool SfiValidator::validate(const vector<CodeSegment>& segments,
                            ProblemSink* out) {
  if (ConstructionFailed(out))
    return false;

  uint32_t base = segments[0].begin_addr();
  uint32_t size = segments.back().end_addr() - base;
  AddressSet branches(base, size);
  AddressSet critical(base, size);

  bool complete_success = true;

  for (vector<CodeSegment>::const_iterator it = segments.begin();
      it != segments.end(); ++it) {
    complete_success &= validate_fallthrough(*it, out, &branches, &critical);

    if (!out->should_continue()) {
      return false;
    }
  }

  complete_success &= validate_branches(segments, branches, critical, out);

  return complete_success;
}

static inline bool TypeMatch(Instruction insn1,
                             Instruction insn2,
                             uint32_t mask) {
  return (insn1.Bits() & mask) == (insn2.Bits() & mask);
}

static inline bool IsMov1ImmNotSpecial(Instruction insn, uint32_t* mask) {
  // See A8.8.102.
  // Encoding A1.
  // cond insn    S 0    Rd   imm12
  // 1111 1111 1111 1111 1111 0000 0000 0000
  // Binary constants is GCC extension, which we frown upon.
  *mask = 0xfffff000;
  return (insn.Bits(27, 21) == 0x1d /* 0b0011101 */) &&
         (insn.Bits(19, 16) == 0x0 /* 0b0000 */) &&
         (insn.Bits(15, 12) < 13);
}

static inline bool IsMov2ImmNotSpecial(Instruction insn, uint32_t* mask) {
  // See A8.8.102.
  // Encoding A2 (for ARM starting ARMv6T2), allowing 16-bit immediates.
  // cond insn      imm4 Rd   imm12
  // 1111 1111 1111 0000 1111 0000 0000 0000
  *mask = 0xfff0f000;
  return (insn.Bits(27, 20) == 0x30 /* 0b00110000 */) &&
         (insn.Bits(15, 12) < 13);
}

static inline bool IsMovtImmNotSpecial(Instruction insn, uint32_t* mask) {
  // See A8.8.106.
  // Encoding A1, ARMv6T2, ARMv7, allowing 16 bit immediates.
  // cond insn      imm4 Rd   imm12
  // 1111 1111 1111 0000 1111 0000 0000 0000
  *mask = 0xfff0f000;
  return (insn.Bits(27, 20) == 0x34 /* 0b00110100 */) &&
         (insn.Bits(15, 12) < 13);
}

static inline bool IsMvnImmNotSpecial(Instruction insn, uint32_t* mask) {
  // See A8.8.115.
  // Encoding A1.  ARMv4, ARMv5T, ARMv6, ARMv7.
  // cond  insn   S 0    Rd   imm12
  // 1111 1111 1111 1111 1111 0000 0000 0000
  *mask = 0xfffff000;
  return (insn.Bits(27, 21) == 0x1f /* 0b0011111 */) &&
         (insn.Bits(19, 16) == 0x0  /* 0b0000 */) &&
         (insn.Bits(15, 12) < 13);
}

static inline bool IsOrrImmNotSpecial(Instruction insn, uint32_t* mask) {
  // See A8.8.122.
  // Encoding A1.  ARMv4, ARMv5T, ARMv6, ARMv7.
  // cond insn    S Rn   Rd   imm12
  // 1111 1111 1111 1111 1111 0000 0000 0000
  *mask = 0xfffff000;
  return (insn.Bits(27, 21) == 0x1c /* 0b0011100 */) &&
         (insn.Bits(15, 12) < 13);
}

bool SfiValidator::ValidateSegmentPair(const CodeSegment& old_code,
                                       const CodeSegment& new_code,
                                       ProblemSink* out) {
  if (ConstructionFailed(out))
    return false;

  if ((old_code.begin_addr() != new_code.begin_addr()) ||
      (old_code.end_addr() != new_code.end_addr())) {
    return false;
  }

  NACL_COMPILE_TIME_ASSERT(nacl_arm_dec::kArm32InstSize / 8 == 4);
  for (uintptr_t va = old_code.begin_addr();
       va != old_code.end_addr();
       va += nacl_arm_dec::kArm32InstSize / 8) {
      Instruction old_insn = old_code[va];
      Instruction new_insn = new_code[va];
      if (new_insn.Bits() == old_insn.Bits())
          continue;
      // We allow replacement of immediates in following instructions:
      //  MOV rX, imm; MVN rX, imm; MOVT rX, imm; ORR rX, imm.
      // (and rX is not allowed to be SP, LR, PC).
      // They are needed to allow modification of immediate constants,
      // which is important for updating inline caches in JIT compilers,
      // like one used in V8.
      // And register shall not be PC.
      // TODO(olonho): shall we allow MOV => MVN and vice versa
      // replacement?
      uint32_t mask = 0;
      bool is_safe = false;
      if (IsMov1ImmNotSpecial(new_insn, &mask) ||
          IsMov2ImmNotSpecial(new_insn, &mask) ||
          IsMovtImmNotSpecial(new_insn, &mask) ||
          IsMvnImmNotSpecial(new_insn, &mask)  ||
          IsOrrImmNotSpecial(new_insn, &mask)   )
        is_safe = TypeMatch(old_insn, new_insn, mask);
      if (!is_safe) {
        out->ReportProblem(va, kProblemUnsafe);
        return false;
      }
  }
  return true;
}

bool SfiValidator::CopyCode(const CodeSegment& source_code,
                            CodeSegment& dest_code,
                            NaClCopyInstructionFunc copy_func,
                            ProblemSink* out) {
  if (ConstructionFailed(out))
    return false;

  vector<CodeSegment> segments;
  segments.push_back(source_code);
  if (!validate(segments, out))
      return false;

  // As on ARM all instructions are 4 bytes in size and aligned
  // we don't have to check instruction boundary invariant.
  for (uintptr_t va = source_code.begin_addr();
       va != source_code.end_addr();
       va += nacl_arm_dec::kArm32InstSize / 8) {
    intptr_t offset = va - source_code.begin_addr();
    // TODO(olonho): this const cast is a bit ugly, but we
    // need to write to dest segment.
    copy_func(const_cast<uint8_t*>(dest_code.base()) + offset,
              const_cast<uint8_t*>(source_code.base()) + offset,
              nacl_arm_dec::kArm32InstSize / 8);
  }

  return true;
}

bool SfiValidator::ConstructionFailed(ProblemSink* out) {
  if (construction_failed_) {
    uint32_t invalid_addr = ~(uint32_t)0;
    out->ReportProblem(invalid_addr, kProblemConstructionFailed);
  }
  return construction_failed_;
}

bool SfiValidator::validate_fallthrough(const CodeSegment& segment,
                                        ProblemSink* out,
                                        AddressSet* branches,
                                        AddressSet* critical) {
  bool complete_success = true;

  nacl_arm_dec::Forbidden initial_decoder;
  // Initialize the previous instruction to a scary BKPT, so patterns all fail.
  DecodedInstruction pred(
      0,  // Virtual address 0, which will be in a different bundle;
      Instruction(0xE1277777),  // The literal-pool-header BKPT instruction;
      initial_decoder);  // and ensure that it decodes as Forbidden.

  for (uint32_t va = segment.begin_addr(); va != segment.end_addr(); va += 4) {
    DecodedInstruction inst(va, segment[va],
                            decode_state_.decode(segment[va]));

    if (inst.safety() != nacl_arm_dec::MAY_BE_SAFE) {
      out->ReportProblemSafety(va, inst.safety());
      if (!out->should_continue()) {
        return false;
      }
      complete_success = false;
    }

    complete_success &= apply_patterns(inst, out);
    if (!out->should_continue()) return false;

    complete_success &= apply_patterns(pred, inst, critical, out);
    if (!out->should_continue()) return false;

    if (inst.is_relative_branch()) {
      branches->add(inst.addr());
    }

    if (inst.is_literal_pool_head()
        && is_bundle_head(inst.addr())) {
      // Add each instruction in this bundle to the critical set.
      uint32_t last_data_addr = bundle_for_address(va).end_addr();
      for (; va != last_data_addr; va += 4) {
        critical->add(va);
      }

      // Decrement the virtual address by one instruction, so the for
      // loop can bump it back forward.  This is slightly dirty.
      va -= 4;
    }

    pred.Copy(inst);
  }

  return complete_success;
}

static bool address_contained(uint32_t va, const vector<CodeSegment>& segs) {
  for (vector<CodeSegment>::const_iterator it = segs.begin(); it != segs.end();
      ++it) {
    if (it->contains_address(va)) return true;
  }
  return false;
}

bool SfiValidator::validate_branches(const vector<CodeSegment>& segments,
                                     const AddressSet& branches,
                                     const AddressSet& critical,
                                     ProblemSink* out) {
  bool complete_success = true;

  vector<CodeSegment>::const_iterator seg_it = segments.begin();

  for (AddressSet::Iterator it = branches.begin(); it != branches.end(); ++it) {
    uint32_t va = *it;

    // Invariant: all addresses in branches are covered by some segment;
    // segments are in sorted order.
    while (!seg_it->contains_address(va)) {
      ++seg_it;
    }

    const CodeSegment &segment = *seg_it;

    DecodedInstruction inst(va, segment[va],
                            decode_state_.decode(segment[va]));

    // We know it is_relative_branch(), so we can simply call:
    uint32_t target_va = inst.branch_target();
    if (address_contained(target_va, segments)) {
      if (critical.contains(target_va)) {
        out->ReportProblemAddress(va, kProblemBranchSplitsPattern, target_va);
        if (!out->should_continue()) {
          return false;
        }
        complete_success = false;
      }
    } else if ((target_va & code_address_mask()) == 0) {
      // Allow bundle-aligned, in-range direct jump.
    } else {
      out->ReportProblemAddress(va, kProblemBranchInvalidDest, target_va);
      if (!out->should_continue()) {
        return false;
      }
      complete_success = false;
    }
  }

  return complete_success;
}

bool SfiValidator::apply_patterns(const DecodedInstruction& inst,
    ProblemSink* out) {
  // Single-instruction patterns. Should return PATTERN_SAFE if the
  // pattern succeeds.
  typedef PatternMatch (*OneInstPattern)(const SfiValidator&,
                                         const DecodedInstruction&,
                                         ProblemSink*);
  static const OneInstPattern one_inst_patterns[] = {
    &check_read_only,
    &check_pc_writes,
    &check_call_position,
  };

  bool complete_success = true;

  for (uint32_t i = 0; i < NACL_ARRAY_SIZE(one_inst_patterns); i++) {
    PatternMatch r = one_inst_patterns[i](*this, inst, out);
    switch (r) {
      case PATTERN_SAFE:
      case NO_MATCH:
        break;

      case PATTERN_UNSAFE:
        complete_success = false;
        break;
    }
  }

  return complete_success;
}

bool SfiValidator::apply_patterns(
    const DecodedInstruction& first, const DecodedInstruction& second,
    AddressSet* critical, ProblemSink* out) {
  // Type for two-instruction pattern functions.
  //
  // Note: These functions can recognize single instruction patterns,
  // as well as two instruction patterns. In addition, single instruction
  // patterns should be applied to the "second" instruction. The main reason for
  // allowing both pattern lengths is so that precondition tests can
  // be shared, and hence more efficient.
  // Arguments are:
  //    sfi - The validator that made the request.
  //    first - The first instruction in the instruction pair.
  //    second - The second instruction in the instruction pair.
  //    match_data - The data collected about the pattern being applied.
  typedef void (*TwoInstPattern)(
      const SfiValidator& sfi,
      const DecodedInstruction& first,
      const DecodedInstruction& second,
      InstructionPairMatchData* match_data);

  // The list of patterns -- defined in static functions up top.
  static const TwoInstPattern two_inst_patterns[] = {
    &check_loadstore_mask,
    &check_branch_mask,
    &check_data_register_update,
  };

  bool complete_success = true;

  for (uint32_t i = 0; i < NACL_ARRAY_SIZE(two_inst_patterns); i++) {
    InstructionPairMatchData match_data(out);
    two_inst_patterns[i](*this, first, second, &match_data);
    switch (match_data.match_) {
      case NO_MATCH: break;

      case PATTERN_UNSAFE:
        // Pattern is in charge of reporting specific issue.
        complete_success = false;
        break;

      case PATTERN_SAFE:
        if (match_data.is_single_instruction_pattern_) break;
        if (bundle_for_address(first.addr())
            != bundle_for_address(second.addr())) {
          complete_success = false;
          if (match_data.problem_ == kValidatorProblemSize) {
            // Specific test pattern did not specify what problem was
            // being worked on. Generate a generic error message.
            out->ReportProblemInstructionPair(
                (match_data.first_is_basis_ ? first.addr() : second.addr()),
                kProblemPatternCrossesBundle,
                kNoSpecificPairProblem,
                first, second);
          } else {
            // Specific test pattern specified what problem was
            // being worked on. Generate message to communiate
            // this.
            out->ReportProblemInstructionPair(
                (match_data.first_is_basis_ ? first.addr() : second.addr()),
                match_data.problem_,
                kPairCrossesBundle,
                first, second);
          }
        } else {
          critical->add(second.addr());
        }
        break;
    }
  }
  return complete_success;
}

bool SfiValidator::is_data_address_register(Register r) const {
  return data_address_registers_.Contains(r);
}

const Bundle SfiValidator::bundle_for_address(uint32_t address) const {
  uint32_t base = address & ~(bytes_per_bundle_ - 1);
  return Bundle(base, bytes_per_bundle_);
}

bool SfiValidator::is_bundle_head(uint32_t address) const {
  return (address & (bytes_per_bundle_ - 1)) == 0;
}

// We eagerly compute both safety and defs here, because it turns out to be
// faster by 10% than doing either lazily and memoizing the result.
DecodedInstruction::DecodedInstruction(uint32_t vaddr,
                                       Instruction inst,
                                       const ClassDecoder& decoder)
    : vaddr_(vaddr),
      inst_(inst),
      decoder_(&decoder),
      safety_(decoder.safety(inst_)),
      defs_(decoder.defs(inst_))
{}

}  // namespace nacl_arm_val
