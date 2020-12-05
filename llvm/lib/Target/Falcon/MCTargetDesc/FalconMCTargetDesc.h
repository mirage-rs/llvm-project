//===-- FalconMCTargetDesc.h - Falcon Target Descriptions -------*- C++ -*-===//
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

#ifndef LLVM_TARGET_FALCON_MCTARGET_DESC_H
#define LLVM_TARGET_FALCON_MCTARGET_DESC_H

#include <memory>

#include "llvm/Support/DataTypes.h"

namespace llvm {

class MCAsmBackend;
class MCCodeEmitter;
class MCContext;
class MCInstrInfo;
class MCObjectTargetWriter;
class MCRegisterInfo;
class MCSubtargetInfo;
class MCTargetOptions;
class Target;

MCInstrInfo *createFalconMCInstrInfo();

/// Creates a machine code emitter for Falcon.
MCCodeEmitter *createFalconMCCodeEmitter(const MCInstrInfo &MCII,
                                         const MCRegisterInfo &MRI,
                                         MCContext &Ctx);

/// Creates an assembly backend for Falcon.
MCAsmBackend *createFalconAsmBackend(const Target &T,
                                     const MCSubtargetInfo &STI,
                                     const MCRegisterInfo &MRI,
                                     const llvm::MCTargetOptions &TO);

/// Creates an ELF object writer for Falcon.
std::unique_ptr<MCObjectTargetWriter>
createFalconELFObjectWriter(raw_pwrite_stream &OS, uint8_t OSABI);

} // end namespace llvm

#define GET_REGINFO_ENUM
#include "FalconGenRegisterInfo.inc"

#define GET_INSTRINFO_ENUM
#include "FalconGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "FalconGenSubtargetInfo.inc"

#endif // LLVM_TARGET_FALCON_MCTARGET_DESC_H
