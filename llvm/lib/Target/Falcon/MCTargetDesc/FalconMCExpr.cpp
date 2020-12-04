//===-- FalconMCExpr.cpp - Falcon-specific MC expression classes ----------===//
//
// Part of the LLVM fork for the Mirage project, under the Apache License v2.0
// with LLVM Exceptions. See https://llvm.org/LICENSE.txt for license
// information.
// SPDX-License-Identifier: Apache-2.0 with LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "FalconMCExpr.h"

#include "llvm/MC/MCAsmLayout.h"
#include "llvm/MC/MCAssembler.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCValue.h"

#define DEBUG_TYPE "falconmcexpr"

namespace llvm {

const FalconMCExpr *FalconMCExpr::create(VariantKind Kind, const MCExpr *Expr,
                                         MCContext &Ctx) {
  return new (Ctx) FalconMCExpr(Kind, Expr);
}

} // end namespace llvm
