//===-- FalconMCInstLower.cpp - Convert Falcon MachineInstr to MCInst -----===//
//
// Part of the LLVM fork for the Mirage project, under the Apache License v2.0
// with LLVM Exceptions. See https://llvm.org/LICENSE.txt for license
// information.
// SPDX-License-Identifier: Apache-2.0 with LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains code to lower Falcon MachineInstrs to their corresponding
// MCInst records.
//
//===----------------------------------------------------------------------===//

#include "FalconMCInstLower.h"

#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/IR/Mangler.h"
#include "llvm/MC/MCInst.h"
#include "llvm/Support/ErrorHandling.h"

#include "MCTargetDesc/FalconMCExpr.h"

namespace llvm {

FalconMCInstLower::FalconMCInstLower(MCContext &Ctx, AsmPrinter &Printer)
    : Ctx(Ctx), AsmPrinter(Printer) {}

void FalconMCInstLower::lowerInstruction(const MachineInstr &MI,
                                         MCInst &OutMI) const {
  OutMI.setOpcode(MI.getOpcode());

  for (const MachineOperand &MO : MI.operands()) {
    MCOperand MCOp;

    switch (MO.getType()) {
    default:
      MI.print(errs());
      llvm_unreachable("unknown operand type");
    case MachineOperand::MO_Register:
      // Ignore all implicit register operands.
      if (MO.isImplicit())
        continue;
      MCOp = MCOperand::createReg(MO.getReg());
      break;
    case MachineOperand::MO_Immediate:
      MCOp = MCOperand::createImm(MO.getImm());
      break;
    case MachineOperand::MO_GlobalAddress:
      MCOp = lowerSymbolOperand(MO, AsmPrinter.GetSymbol(MO.getGlobal()));
      break;
    case MachineOperand::MO_ExternalSymbol:
      MCOp = lowerSymbolOperand(
          MO, AsmPrinter.GetExternalSymbolSymbol(MO.getSymbolName()));
      break;
    case MachineOperand::MO_MachineBasicBlock:
      MCOp = MCOperand::createExpr(
          MCSymbolRefExpr::create(MO.getMBB()->getSymbol(), Ctx));
      break;
    case MachineOperand::MO_RegisterMask:
      continue;
    case MachineOperand::MO_BlockAddress:
      MCOp = lowerSymbolOperand(
          MO, AsmPrinter.GetBlockAddressSymbol(MO.getBlockAddress()));
      break;
    }

    OutMI.addOperand(MCOp);
  }
}

MCOperand FalconMCInstLower::lowerSymbolOperand(const MachineOperand &MO,
                                                MCSymbol *Sym) const {
  unsigned char TF = MO.getTargetFlags();
  const MCExpr *Expr = MCSymbolRefExpr::create(Sym, Ctx);

  if (!MO.isJTI() && MO.getOffset()) {
    Expr = MCBinaryExpr::createAdd(
        Expr, MCConstantExpr::create(MO.getOffset(), Ctx), Ctx);
  }

  // TODO: Generate proper expressions.

  return MCOperand::createExpr(Expr);
}

} // end namespace llvm
