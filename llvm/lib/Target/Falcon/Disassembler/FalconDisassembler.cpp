//===- FalconDisassembler.cpp - Disassembler for Falcon -------------------===//
//
// Part of the LLVM fork for the Mirage project, under the Apache License v2.0
// with LLVM Exceptions. See https://llvm.org/LICENSE.txt for license
// information.
// SPDX-License-Identifier: Apache-2.0 with LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file is part of the Falcon Disassembler.
//
//===----------------------------------------------------------------------===//

#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCDisassembler/MCDisassembler.h"
#include "llvm/MC/MCFixedLenDisassembler.h"
#include "llvm/MC/MCInst.h"
#include "llvm/Support/TargetRegistry.h"

#include "Falcon.h"
#include "FalconRegisterInfo.h"
#include "FalconSubtarget.h"
#include "MCTargetDesc/FalconMCTargetDesc.h"
#include "TargetInfo/FalconTargetInfo.h"

#define DEBUG_TYPE "falcon-disassembler"

namespace llvm {

using DecodeStatus = MCDisassembler::DecodeStatus;

namespace {

/// A disassembler class for Falcon.
class FalconDisassembler : public MCDisassembler {
public:
  FalconDisassembler(const MCSubtargetInfo &STI, MCContext &Ctx)
      : MCDisassembler(STI, Ctx) {}

  virtual ~FalconDisassembler() {}

  DecodeStatus getInstruction(MCInst &Instr, uint64_t &Size,
                              ArrayRef<uint8_t> Bytes, uint64_t Address,
                              raw_ostream &CStream) const override;
};

} // end namespace

static MCDisassembler *createFalconDisassembler(const Target &T,
                                                const MCSubtargetInfo &STI,
                                                MCContext &Ctx) {
  return new FalconDisassembler(STI, Ctx);
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeFalconDisassembler() {
  // Register the disassembler.
  TargetRegistry::RegisterMCDisassembler(getTheFalconTarget(),
                                         createFalconDisassembler);
}

DecodeStatus FalconDisassembler::getInstruction(MCInst &Instr, uint64_t &Size,
                                                ArrayRef<uint8_t> Bytes,
                                                uint64_t Address,
                                                raw_ostream &CStream) const {
  uint64_t Insn;

  llvm_unreachable("getInstruction() unimplemented");
  return MCDisassembler::Fail;
}

} // end namespace llvm
