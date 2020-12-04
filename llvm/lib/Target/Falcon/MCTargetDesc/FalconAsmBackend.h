//===-- FalconAsmBackend.h - Falcon Asm Backend  ----------------*- C++ -*-===//
//
// Part of the LLVM fork for the Mirage project, under the Apache License v2.0
// with LLVM Exceptions. See https://llvm.org/LICENSE.txt for license
// information.
// SPDX-License-Identifier: Apache-2.0 with LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// The Falcon assembly backend implementation.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_TARGET_FALCON_ASM_BACKEND_H
#define LLVM_TARGET_FALCON_ASM_BACKEND_H

#include "llvm/MC/MCAsmBackend.h"

#include "MCTargetDesc/FalconFixupKinds.h"

namespace llvm {

class MCAssembler;
struct MCFixupKindInfo;

/// Utilities for manipulating generated Falcon machine code.
class FalconAsmBackend : public MCAsmBackend {
public:
  FalconAsmBackend() : MCAsmBackend(support::little) {}

  void adjustFixupValue(const MCFixup &Fixup, const MCValue &Target,
                        uint64_t &Value, MCContext *Ctx = nullptr) const;

  std::unique_ptr<MCObjectTargetWriter>
  createObjectTargetWriter(raw_pwrite_stream &OS) const override;

  void applyFixup(const MCAssembler &Asm, const MCFixup &Fixup,
                  const MCValue &Target, MutableArrayRef<char> Data,
                  uint64_t Value, bool IsResolved,
                  const MCSubtargetInfo *STI) const override;

  const MCFixupKindInfo &getFixupKindInfo(MCFixupKind Kind) const override;

  unsigned getNumFixupKinds() const override {
    return Falcon::NumTargetFixupKinds;
  }

  bool mayNeedRelaxation(const MCInst &Inst,
                         const MCSubtargetInfo &STI) const override {
    // FIXME
    return false;
  }

  bool fixupNeedsRelaxation(const MCFixup &Fixup, uint64_t Value,
                            const MCRelaxableFragment *DF,
                            const MCAsmLayout &Layout) const override {
    // FIXME
    llvm_unreachable("RelaxInstruction() unimplemented");
    return false;
  }

  bool writeNopData(raw_ostream &OS, uint64_t Count) const override;

  bool shouldForceRelocation(const MCAssembler &Asm, const MCFixup &Fixup,
                             const MCValue &Target) override;
};

} // end namespace llvm

#endif // LLVM_TARGET_FALCON_ASM_BACKEND_H
