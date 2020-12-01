//===-- FalconFrameLowering.cpp - Falcon Frame Information ----------------===//
//
// Part of the LLVM fork for the Mirage project, under the Apache License v2.0
// with LLVM Exceptions. See https://llvm.org/LICENSE.txt for license
// information.
// SPDX-License-Identifier: Apache-2.0 with LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the Falcon implementation of TargetFrameLowering class.
//
//===----------------------------------------------------------------------===//

#include "FalconFrameLowering.h"

#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegionInfo.h"

#include "FalconInstrInfo.h"
#include "FalconSubtarget.h"

namespace llvm {

FalconFrameLowering::FalconFrameLowering()
    : TargetFrameLowering(TargetFrameLowering::StackGrowsDown, Align(4), 0,
                          Align(4)) {}

// TODO: Prologue and Epilogue.

void FalconFrameLowering::emitPrologue(MachineFunction &MF,
                                       MachineBasicBlock &MBB) const {}

void FalconFrameLowering::emitEpilogue(MachineFunction &MF,
                                       MachineBasicBlock &MBB) const {}

bool FalconFrameLowering::hasFP(const MachineFunction &MF) const {
  return MF.getFrameInfo().hasVarSizedObjects();
}

bool FalconFrameLowering::isFPCloseToIncomingSP() const { return false; }

void FalconFrameLowering::determineCalleeSaves(MachineFunction &MF,
                                               BitVector &SavedRegs,
                                               RegScavenger *RS) const {
  TargetFrameLowering::determineCalleeSaves(MF, SavedRegs, RS);
}

MachineBasicBlock::iterator FalconFrameLowering::eliminateCallFramePseudoInstr(
    MachineFunction &MF, MachineBasicBlock &MBB,
    MachineBasicBlock::iterator I) const {
  return MBB.erase(I);
}

int FalconFrameLowering::getFrameIndexReference(const MachineFunction &MF,
                                                int FI,
                                                Register &FrameReg) const {
  const FalconSubtarget &Subtarget = MF.getSubtarget<FalconSubtarget>();
  const MachineFrameInfo &MFI = MF.getFrameInfo();
  const FalconRegisterInfo *RegInfo = Subtarget.getRegisterInfo();

  // Fill in FrameReg output argument.
  FrameReg = RegInfo->getFrameRegister(MF);

  // Start with the offset of FI from the top of the allocated frame.
  // As the stack grows downwards, this offset will be negative.
  int64_t FrameOffset = MFI.getObjectOffset(FI) + MFI.getOffsetAdjustment();
  // Make the frame offset relative to the incoming stack pointer.
  FrameOffset -= getOffsetOfLocalArea();
  // Make the frame offset relative to the bottom of the frame.
  FrameOffset += MFI.getStackSize();

  return FrameOffset;
}

} // end namespace llvm
