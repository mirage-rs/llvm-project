//===-- FalconMCTargetDesc.cpp - Falcon Target Descriptions ---------------===//
//
// Part of the LLVM fork for the Mirage project, under the Apache License v2.0
// with LLVM Exceptions. See https://llvm.org/LICENSE.txt for license
// information.
// SPDX-License-Identifier: Apache-2.0 with LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides Falcon-specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "FalconMCTargetDesc.h"

#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCELFStreamer.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/TargetRegistry.h"

#include "FalcnMCAsmInfo.h"
#include "InstPrinter/FalconInstPrinter.h"

#define GET_INSTRINFO_MC_DESC
#include "FalconGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "FalconGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "FalconGenRegisterInfo.inc"

namespace llvm {

MCInstrInfo *createFalconMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitFalconMCInstrInfo(X);

  return X;
}

static MCRegisterInfo *createFalconMCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitFalconMCRegisterInfo(X, 0);

  return X;
}

static MCSubtargetInfo *
createFalconMCSubtargetInfo(const Triple &TT, StringRef CPU, StringRef FS) {
  return createFalconMCSubtargetInfoImpl(TT, CPU, FS);
}

static MCInstPrinter *createFalconMCInstPrinter(const Triple &TT,
                                                unsigned SyntaxVariant,
                                                const MCAsmInfo &MAI,
                                                const MCInstrInfo &MII,
                                                const MCRegisterInfo &MRI) {
  if (SyntaxVariant == 0)
    return new FalconInstPrinter(MAI, MII, MRI);

  return nullptr;
}

static MCStreamer *createMCStreamer(const Triple &TT, MCContext &Context,
                                    std::unique_ptr<MCAsmBackend> &&MAB,
                                    std::unique_ptr<MCObjectWriter> &&OW,
                                    std::unique_ptr<MCCodeEmitter> &&Emitter,
                                    bool RelaxAll) {
  return createELFStreamer(Context, std::move(MAB), std::move(OW),
                           std::move(Emitter), RelaxAll);
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeFalconTargetMC() {
  // Register the MC ASM info.
  RegisterMCAsmInfo<FalconMCAsmInfo> X(getTheFalconTarget());

  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(getTheFalconTarget(),
                                      createFalconMCInstrInfo);

  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(getTheFalconTarget(),
                                    createFalconMCRegisterInfo);

  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(getTheFalconTarget(),
                                          createFalconMCSubtargetInfo);

  // Register the MCInstPrinter.
  TargetRegistry::RegisterMCInstPrinter(getTheFalconTarget(),
                                        createFalconMCInstPrinter);

  // Register the MC Code Emitter.
  TargetRegistry::RegisterMCCodeEmitter(getTheFalconTarget(),
                                        createFalconMCCodeEmitter);

  // Register the object streamer.
  TargetRegistry::RegisterELFStreamer(getTheFalconTarget(), createMCStreamer);

  // Register the ASM backend (as little endian).
  TargetRegistry::RegisterMCAsmBackend(getTheFalconTarget(),
                                       createFalconAsmBackend);
}

} // end namespace llvm
