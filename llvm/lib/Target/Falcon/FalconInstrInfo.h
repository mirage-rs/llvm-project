//===-- FalconInstrInfo.h - Falcon Instruction Information ------*- C++ -*-===//
//
// Part of the LLVM fork for the Mirage project, under the Apache License v2.0
// with LLVM Exceptions. See https://llvm.org/LICENSE.txt for license
// information.
// SPDX-License-Identifier: Apache-2.0 with LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the Falcon implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_TARGET_FALCON_INSTR_INFO_H
#define LLVM_TARGET_FALCON_INSTR_INFO_H

#include "llvm/CodeGen/TargetInstrInfo.h"

#include "FalconRegisterInfo.h"

#define GET_INSTRINFO_HEADER
#include "FalconGenInstrInfo.inc"
#undef GET_INSTRINFO_HEADER

namespace llvm {

/// Utilities related to the Falcon instruction set.
class FalconInstrInfo : public FalconGenInstrInfo {
public:
  explicit FalconInstrInfo();

  const FalconRegisterInfo &getRegisterInfo() const { return RI; }

private:
  const FalconRegisterInfo RI;
};

} // end namespace llvm

#endif // LLVM_TARGET_FALCON_INSTR_INFO_H
