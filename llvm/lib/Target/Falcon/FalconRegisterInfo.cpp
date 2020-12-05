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

const MCPhysReg *
FalconRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  return CSR_SaveList;
}

const uint32_t *
FalconRegisterInfo::getCallPreservedMask(const MachineFunction &MF,
                                         CallingConv::ID CC) const {
  return CSR_RegMask;
}

BitVector FalconRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());
  const TargetFrameLowering *TFI = MF.getSubtarget().getFrameLowering();

  // If a dedicated Frame Pointer is being used, reserve it here. Otherwise,
  // we can alternatively wait for the Stack Pointer to be reserved later on.
  if (TFI->hasFP(MF)) {
    Reserved.set(Falcon::R0);
    Reserved.set(Falcon::R0H);
    Reserved.set(Falcon::R0B);
  }

  // Reserve all the Falcon special-purpose registers. We don't want these
  // to be allocated at any point because they serve a different purpose.
  Reserved.set(Falcon::IV0);
  Reserved.set(Falcon::IV1);
  Reserved.set(Falcon::IV2);
  Reserved.set(Falcon::EV);
  Reserved.set(Falcon::SP);
  Reserved.set(Falcon::PC);
  Reserved.set(Falcon::IMB);
  Reserved.set(Falcon::DMB);
  Reserved.set(Falcon::CSW);
  Reserved.set(Falcon::CCR);
  Reserved.set(Falcon::SCP);
  Reserved.set(Falcon::CTX);
  Reserved.set(Falcon::EXCI);
  Reserved.set(Falcon::SEC1);
  Reserved.set(Falcon::IMB1);
  Reserved.set(Falcon::DMB1);

  // Reserve all the Falcon crypto registers. These can only be accessed by
  // crypto commands under special conditions and should never be allocated.
  Reserved.set(Falcon::C0);
  Reserved.set(Falcon::C1);
  Reserved.set(Falcon::C2);
  Reserved.set(Falcon::C3);
  Reserved.set(Falcon::C4);
  Reserved.set(Falcon::C5);
  Reserved.set(Falcon::C6);
  Reserved.set(Falcon::C7);

  return Reserved;
}

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
