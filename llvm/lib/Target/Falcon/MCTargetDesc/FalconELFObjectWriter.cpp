//===-- FalconELFObjectWriter.cpp - Falcon ELF Writer ---------------------===//
//
// Part of the LLVM fork for the Mirage project, under the Apache License v2.0
// with LLVM Exceptions. See https://llvm.org/LICENSE.txt for license
// information.
// SPDX-License-Identifier: Apache-2.0 with LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "llvm/MC/MCAssembler.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCSection.h"
#include "llvm/MC/MCValue.h"
#include "llvm/Support/ErrorHandling.h"

#include "MCTargetDesc/FalconFixupKinds.h"
#include "MCTargetDesc/FalconMCTargetDesc.h"

namespace llvm {

/// Writes Falcon machine code into an ELF32 object file.
class FalconELFObjectWriter : public MCELFObjectTargetWriter {
public:
  FalconELFObjectWriter(uint8_t OSABI);

  virtual ~FalconELFObjectWriter() {}

  unsigned getRelocType(MCContext &Ctx, const MCValue &Target,
                        const MCFixup &Fixup, bool IsPCRel) const override;
};

FalconELFObjectWriter::FalconELFObjectWriter(uint8_t OSABI)
    : MCELFObjectTargetWriter(false, OSABI, ELF::EM_FALCON, true) {}

unsigned FalconELFObjectWriter::getRelocType(MCContext &Ctx,
                                             const MCValue &Target,
                                             const MCFixup &Fixup,
                                             bool IsPCRel) const {
  // TODO
  llvm_unreachable("getRelocType() unimplemented");
  return 0;
}

std::unique_ptr<MCObjectTargetWriter>
createFalconELFObjectWriter(uint8_t OSABI) {
  return std::make_unique<FalconELFObjectWriter>(OSABI);
}

} // end namespace llvm
