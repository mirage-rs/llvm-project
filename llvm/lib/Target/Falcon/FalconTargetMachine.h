//===-- FalconTargetMachine.h - Define TargetMachine for Falcon -*- C++ -*-===//
//
// Part of the LLVM fork for the Mirage project, under the Apache License v2.0
// with LLVM Exceptions. See https://llvm.org/LICENSE.txt for license
// information.
// SPDX-License-Identifier: Apache-2.0 with LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares the Falcon specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_TARGET_FALCON_TARGET_MACHINE_H
#define LLVM_TARGET_FALCON_TARGET_MACHINE_H

#include "llvm/Target/TargetMachine.h"

#include "FalconInstrInfo.h"
#include "FalconSubtarget.h"

namespace llvm {

/// A generic Falcon implementation.
class FalconTargetMachine : public LLVMTargetMachine {
public:
  FalconTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                      StringRef FS, const TargetOptions &Options,
                      Optional<Reloc::Model> RM, Optional<CodeModel::Model> CM,
                      CodeGenOpt::Level OL, bool JIT);

  const FalconSubtarget *getSubtargetImpl() const;
  const FalconSubtarget *getSubtargetImpl(const Function &) const override;

  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }

  // Pass Pipeline Configuration
  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;

  bool isMachineVerifierClean() const override { return false; }

private:
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
  FalconSubtarget SubTarget;
};

} // end namespace llvm

#endif // LLVM_TARGET_FALCON_TARGET_MACHINE_H
