//===-- FalconSubtarget.cpp - Falcon Subtarget Information ----------------===//
//
// Part of the LLVM fork for the Mirage project, under the Apache License v2.0
// with LLVM Exceptions. See https://llvm.org/LICENSE.txt for license
// information.
// SPDX-License-Identifier: Apache-2.0 with LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements the Falcon-specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#include "FalconSubtarget.h"

#include "llvm/Support/TargetRegistry.h"

#include "Falcon.h"
#include "FalconTargetMachine.h"
#include "MCTargetDesc/FalconMCTargetDesc.h"

#define DEBUG_TYPE "falcon-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "FalconGenSubtargetInfo.inc"

namespace llvm {

// Pin the VTable to this file.
void FalconSubtarget::anchor() {}

FalconSubtarget::FalconSubtarget(const Triple &TT, const std::string &CPU,
                                 const std::string &FS, const TargetMachine &TM)
    : FalconGenSubtargetInfo(TT, CPU, FS),

      // Subtarget features
      HasSCP(false),

      InstrInfo(), FrameLowering(),
      TLInfo(TM, initializeSubtargetDependencies(CPU, FS, TM)) TSInfo() {
  // Parse features string.
  ParseSubtargetFeatures(CPU, FS);
}

FalconSubtarget &
FalconSubtarget::initializeSubtargetDependencies(StringRef CPU, StringRef FS,
                                                 const TargetMachine &TM) {
  // Parse features string.
  ParseSubtargetFeatures(CPU, FS);
  return *this;
}

} // end namespace llvm
