//===-- FalconMCExpr.h - Falcon-specific MC expression classes --*- C++ -*-===//
//
// Part of the LLVM fork for the Mirage project, under the Apache License v2.0
// with LLVM Exceptions. See https://llvm.org/LICENSE.txt for license
// information.
// SPDX-License-Identifier: Apache-2.0 with LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_TARGET_FALCON_MCEXPR_H
#define LLVM_TARGET_FALCON_MCEXPR_H

#include "llvm/MC/MCExpr.h"

#include "MCTargetDesc/FalconFixupKinds.h"

namespace llvm {

/// An expression in Falcon machine code.
class FalconMCExpr : public MCTargetExpr {
public:
  /// Specifies the type of an expression.
  enum VariantKind {
    VK_Falcon_None,
    // TODO
  };

public:
  /// Creates an AVR machine code expression.
  static const FalconMCExpr *create(VariantKind Kind, const MCExpr *Expr,
                                    MCContext &Ctx);

private:
  const VariantKind Kind;
  const MCExpr *SubExpr;

  explicit FalconMCExpr(VariantKind Kind, const MCExpr *Expr)
      : Kind(Kind), SubExpr(Expr) {}

  ~FalconMCExpr() {}
};

} // end namespace llvm

#endif // LLVM_TARGET_FALCON_MCEXPR_H
