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

#include "Falcon.h"
#include "FalconTargetObjectFile.h"
#include "TargetInfo/FalconTargetInfo.h"

namespace llvm {

static const char *FalconDataLayout = ""; // TODO

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeFalconTarget() {
  // Register the target.
  RegisterTargetMachine<FalconTargetMachine> X(getTheFalconTarget());
}

static Reloc::Model getEffectiveRelocModel(Optional<Reloc::Model> RM) {
  return RM.hasValue() ? *RM : Reloc::Static;
}

FalconTargetMachine::FalconTargetMachine(const Target &T, const Triple &TT,
                                         StringRef CPU, StringRef FS,
                                         const TargetOptions &Options,
                                         Optional<Reloc::Model> RM,
                                         Optional<CodeModel::Model> CM,
                                         CodeGenOpt::Level OL, bool JIT)
    : LLVMTargetMachine(T, FalconDataLayout, TT, CPU, FS, Options,
                        getEffectiveRelocModel(RM), CM, OL),
      TLOF(std::make_unique<FalconTargetObjectFile>()),
      SubTarget(TT, CPU, FS, *this) {
  initAsmInfo();
}

namespace {
/// Falcon Code Generator Pass Configuration Options.
class FalconPassConfig : public TargetPassConfig {
public:
  FalconPassConfig(FalconTargetMachine &TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  FalconTargetMachine &getFalconTargetMachine() const {
    return getTM<FalconTargetMachine>();
  }

  bool addInstSelector() override;
};
} // end namespace

TargetPassConfig *FalconTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new FalconPassConfig(*this, PM);
}

const FalconSubtarget *FalconTargetMachine::getSubtargetImpl() const {
  return &SubTarget;
}

const FalconSubtarget *
FalconTargetMachine::getSubtargetImpl(const Function &) const {
  return &SubTarget;
}

//===----------------------------------------------------------------------===//
// Pass Pipeline Configuration
//===----------------------------------------------------------------------===//

bool FalconPassConfig::addInstSelector() {
  // Install an instruction selector.
  addPass(createFalconISelDag(getFalconTargetMachine(), getOptLevel()));

  return false;
}

} // end namespace llvm
