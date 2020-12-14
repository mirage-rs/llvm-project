//===-- FalconISelLowering.cpp - Falcon DAG Lowering Implementation -------===//
//
// Part of the LLVM fork for the Mirage project, under the Apache License v2.0
// with LLVM Exceptions. See https://llvm.org/LICENSE.txt for license
// information.
// SPDX-License-Identifier: Apache-2.0 with LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file defines the interfaces that Falcon uses to lower LLVM code into a
// selection DAG.
//
//===----------------------------------------------------------------------===//

#include "FalconISelLowering.h"

#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/StringSwitch.h"
#include "llvm/CodeGen/CallingConvLower.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/ErrorHandling.h"

#include "Falcon.h"
#include "FalconMachineFunctionInfo.h"
#include "FalconSubtarget.h"
#include "FalconTargetMachine.h"
#include "MCTargetDesc/FalconMCTargetDesc.h"

namespace llvm {

FalconTargetLowering::FalconTargetLowering(const FalconTargetMachine &TM,
                                           const FalconSubtarget &STI)
    : TargetLowering(TM), Subtarget(STI) {
  // Set up the register classes.
  addRegisterClass(MVT::i8, &Falcon::GPR8RegClass);
  addRegisterClass(MVT::i16, &Falcon::GPR16RegClass);
  addRegisterClass(MVT::i32, &Falcon::GPR32RegClass);

  // Compute derived properties from the register classes.
  computeRegisterProperties(Subtarget.getRegisterInfo());

  setStackPointerRegisterToSaveRestore(Falcon::SP);
}

const char *FalconTargetLowering::getTargetNodeName(unsigned Opcode) const {
#define NODE(name)                                                             \
  case FalconISD::name:                                                        \
    return #name

  switch (Opcode) {
  default:
    return nullptr;
    // TODO: Populate this.
#undef NODE
  }
}

SDValue FalconTargetLowering::LowerOperation(SDValue Op,
                                             SelectionDAG &DAG) const {
  // TODO
  llvm_unreachable("LowerOperation() unimplemented");
}

MachineBasicBlock *FalconTargetLowering::EmitInstrWithCustomInserter(
    MachineInstr &MI, MachineBasicBlock *MBB) const {
  // TODO
  llvm_unreachable("EmitInstrWithCustomInserter() unimplemented");
}

} // end namespace llvm
