//===-- FalconTargetInfo.cpp - Falcon Target Implementation ---------------===//
//
// Part of the LLVM fork for the Mirage project, under the Apache License v2.0
// with LLVM Exceptions. See https://llvm.org/LICENSE.txt for license
// information.
// SPDX-License-Identifier: Apache-2.0 with LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "TargetInfo/FalconTargetInfo.h"

#include "llvm/Support/TargetRegistry.h"

namespace llvm {

Target &getTheFalconTarget() {
  static Target TheFalconTarget;
  return TheFalconTarget;
}

} // end namespace llvm

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeFalconTargetInfo() {
  llvm::RegisterTarget<llvm::Triple::falcon> X(
      llvm::getTheFalconTarget(), "falcon", "NVIDIA Falcon Microprocessor",
      "Falcon");
}
