//===-- FalconISelLowering.h - Falcon DAG Lowering Interface ----*- C++ -*-===//
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

#ifndef LLVM_TARGET_FALCON_ISEL_LOWERING_H
#define LLVM_TARGET_FALCON_ISEL_LOWERING_H

#include "llvm/CodeGen/CallingConvLower.h"
#include "llvm/CodeGen/TargetLowering.h"

namespace llvm {

namespace FalconISD {

/// Falcon-specific DAG Nodes.
enum NodeType {
  // TODO: Populate this.
};

} // end namespace FalconISD

class FalconSubtarget;
class FalconTargetMachine;

/// Performs target lowering for the Falcon.
class FalconTargetLowering : public TargetLowering {
public:
  explicit FalconTargetLowering(const FalconTargetMachine &TM,
                                const FalconSubtarget &STI);

  const char *getTargetNodeName(unsigned Opcode) const override;

  SDValue LowerOperation(SDValue Op, SelectionDAG &DAG) const override;

  MachineBasicBlock *
  EmitInstrWithCustomInserter(MachineInstr &MI,
                              MachineBasicBlock *MBB) const override;

protected:
  const FalconSubtarget &Subtarget;

private:
  // TODO: Implement lowering.
};

} // end namespace llvm

#endif // LLVM_TARGET_FALCON_ISEL_LOWERING_H
