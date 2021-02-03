//===-- FalconTargetMachine.cpp - Define TargetMachine for Falcon ---------===//
//
// Part of the LLVM fork for the Mirage project, under the Apache License v2.0
// with LLVM Exceptions. See https://llvm.org/LICENSE.txt for license
// information.
// SPDX-License-Identifier: Apache-2.0 with LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Implements the info about Falcon target spec.
//
//===----------------------------------------------------------------------===//

#include "FalconTargetMachine.h"

#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Support/TargetRegistry.h"

namespace llvm {

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeFalconTarget() {
  // TODO
}

// TODO

} // end namespace llvm
