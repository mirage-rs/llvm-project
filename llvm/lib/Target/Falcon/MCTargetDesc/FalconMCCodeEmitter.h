//=-- FalconMCCodeEmitter.h - Convert Falcon Code to Machine Code -*- C++ -*-=//
//
// Part of the LLVM fork for the Mirage project, under the Apache License v2.0
// with LLVM Exceptions. See https://llvm.org/LICENSE.txt for license
// information.
// SPDX-License-Identifier: Apache-2.0 with LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file defines the FalconMCCodeEmitter class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_TARGET_FALCON_CODE_EMITTER_H
#define LLVM_TARGET_FALCON_CODE_EMITTER_H

#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/Support/DataTypes.h"

#include "FalconFixupKinds.h"

#define GET_INSTRINFO_OPERAND_TYPES_ENUM
#include "FalconGenInstrInfo.inc"

namespace llvm {

class MCContext;
class MCExpr;
class MCFixup;
class MCInst;
class MCInstrInfo;
class MCOperand;
class MCSubtargetInfo;
class raw_ostream;

/// Writes Falcon machine code to a stream.
class FalconMCCodeEmitter : public MCCodeEmitter {
public:
  FalconMCCodeEmitter(const MCInstrInfo &MCII, MCContext &Ctx)
      : MCII(MCII), Ctx(Ctx) {}

private:
  const MCInstrInfo &MCII;
  MCContext &Ctx;

  FalconMCCodeEmitter(const FalconMCCodeEmitter &) = delete;
  void operator=(const FalconMCCodeEmitter &) = delete;
};

} // end namespace llvm

#endif // LLVM_TARGET_FALCON_CODE_EMITTER_H
