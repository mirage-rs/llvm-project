//===-- FalconMCCodeEmitter.cpp - Convert Falcon Code to Machine Code -----===//
//
// Part of the LLVM fork for the Mirage project, under the Apache License v2.0
// with LLVM Exceptions. See https://llvm.org/LICENSE.txt for license
// information.
// SPDX-License-Identifier: Apache-2.0 with LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements the FalconMCCodeEmitter class.
//
//===----------------------------------------------------------------------===//

#include "FalconMCCodeEmitter.h"

#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCFixup.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/EndianStream.h"
#include "llvm/Support/raw_ostream.h"

#define DEBUG_TYPE "mccodeemitter"

#define GET_INSTRMAP_INFO
#include "FalconGenInstrInfo.inc"
#undef GET_INSTRMAP_INFO

namespace llvm {

// TODO

MCCodeEmitter *createFalconMCCodeEmitter(const MCInstrInfo &MCII,
                                         const MCRegisterInfo &MRI,
                                         MCContext &Ctx) {
  return new FalconMCCodeEmitter(MCII, Ctx);
}

} // end namespace llvm
