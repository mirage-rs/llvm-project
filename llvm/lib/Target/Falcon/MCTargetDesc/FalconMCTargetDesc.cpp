//===-- FalconMCTargetDesc.cpp - Falcon Target Descriptions ---------------===//
//
// Part of the LLVM fork for the Mirage project, under the Apache License v2.0
// with LLVM Exceptions. See https://llvm.org/LICENSE.txt for license
// information.
// SPDX-License-Identifier: Apache-2.0 with LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides Falcon-specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCELFStreamer.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/TargetRegistry.h"

#define GET_INSTRINFO_MC_DESC
#include "FalconGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "FalconGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "FalconGenRegisterInfo.inc"

namespace llvm {

// TODO

} // end namespace llvm

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeFalconTargetMC() {
  // TODO
}
