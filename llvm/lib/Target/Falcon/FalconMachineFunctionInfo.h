//==-- FalconMachineFunctionInfo.h - Falcon machine function info -*- C++ -*-=//
//
// Part of the LLVM fork for the Mirage project, under the Apache License v2.0
// with LLVM Exceptions. See https://llvm.org/LICENSE.txt for license
// information.
// SPDX-License-Identifier: Apache-2.0 with LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares Falcon-specific per-machine-function information.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_TARGET_FALCON_MACHINE_FUNCTION_INFO_H
#define LLVM_TARGET_FALCON_MACHINE_FUNCTION_INFO_H

#include "llvm/CodeGen/MachineFunction.h"

namespace llvm {

/// Contains Falcon-specific information for each MachineFunction.
class FalconMachineFunctionInfo : public MachineFunctionInfo {
public:
  FalconMachineFunctionInfo()
      : VarArgsFrameIndex(0), ReturnAddrFrameIndex(0), FramePointerSaveIndex(0),
        ManipulatesSP(false) {}

  explicit FalconMachineFunctionInfo(MachineFunction &MF)
      : VarArgsFrameIndex(0), ReturnAddrFrameIndex(0), FramePointerSaveIndex(0),
        ManipulatesSP(false) {}

  // Get and set the frame index of the first stack vararg.
  unsigned getVarArgsFrameIndex() const { return VarArgsFrameIndex; }
  void setVarArgsFrameIndex(unsigned FI) { VarArgsFrameIndex = FI; }

  // Get and set the frame index of the return register.
  int getReturnAddrFrameIndex() const { return ReturnAddrFrameIndex; }
  void setReturnAddrFrameIndex(int FI) { ReturnAddrFrameIndex = FI; }

  // Get and set the frame index of where the old frame pointer is stored.
  int getFramePointerSaveIndex() const { return FramePointerSaveIndex; }
  void setFramePointerSaveIndex(int Idx) { FramePointerSaveIndex = Idx; }

  // Get and set whether the function directly manipulates the stack pointer,
  // e.g. through STACKSAVE or STACKRESTORE.
  bool getManipulatesSP() const { return ManipulatesSP; }
  void setManipulatesSP(bool MSP) { ManipulatesSP = MSP; }

private:
  virtual void anchor();

  unsigned VarArgsFrameIndex;
  int ReturnAddrFrameIndex;
  int FramePointerSaveIndex;
  bool ManipulatesSP;
};

} // end namespace llvm

#endif // LLVM_TARGET_FALCON_MACHINE_FUNCTION_INFO_H
