//===-- FalconInstPrinter.cpp - Convert Falcon MCInst to assembly syntax --===//
//
// Part of the LLVM fork for the Mirage project, under the Apache License v2.0
// with LLVM Exceptions. See https://llvm.org/LICENSE.txt for license
// information.
// SPDX-License-Identifier: Apache-2.0 with LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This class prints an Falcon MCInst to a .s file.
//
//===----------------------------------------------------------------------===//

#include "FalconInstPrinter.h"

#include <cstring>

#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrDesc.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"

#include "MCTargetDesc/FalconMCTargetDesc.h"

#define DEBUG_TYPE "asm-printer"

namespace llvm {

// Include the auto-generated portion of the assembly writer.
#define PRINT_ALIAS_INSTR
#include "FalconGenAsmWriter.inc"

void FalconInstPrinter::printInst(const MCInst *MI, uint64_t Address,
                                  StringRef Annot, const MCSubtargetInfo &STI,
                                  raw_ostream &O) {
  unsigned Opcode = MI->getOpcode();

  // TODO
  llvm_unreachable("printInst() unimplemented");
}

void FalconInstPrinter::printOperand(const MCInst *MI, unsigned OpNo,
                                     raw_ostream &O) {
  // TODO
  llvm_unreachable("printOperand() unimplemented");
}

void FalconInstPrinter::printPCRelImm(const MCInst *MI, unsigned OpNo, raw_ostream &O) {
  // TODO
  llvm_unreachable("printPCRelImm() unimplemented");
}

} // end namespace llvm
