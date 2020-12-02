//===-- FalconRegisterInfo.cpp - Falcon Register Information --------------===//
//
// Part of the LLVM fork for the Mirage project, under the Apache License v2.0
// with LLVM Exceptions. See https://llvm.org/LICENSE.txt for license
// information.
// SPDX-License-Identifier: Apache-2.0 with LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the Falcon implementation of the TargetRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#include "FalconRegisterInfo.h"

#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/CodeGen/TargetFrameLowering.h"
#include "llvm/IR/Function.h"

#include "Falcon.h"
#include "FalconSubtarget.h"
#include "FalconTargetMachine.h"

#define GET_REGINFO_TARGET_DESC
#include "FalconGenRegisterInfo.inc"

namespace llvm {

FalconRegisterInfo::FalconRegisterInfo() : FalconGenRegisterInfo(Falcon::PC) {}

void FalconRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator MI,
                                             int SPAdj, unsigned FIOperandNum,
                                             RegScavenger *RS) const {
  // TODO
}

Register FalconRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  const TargetFrameLowering *TFI = MF.getSubtarget().getFrameLowering();
  return TFI->hasFP(MF) ? Falcon::R0 : Falcon::SP;
}

} // end namespace llvm
