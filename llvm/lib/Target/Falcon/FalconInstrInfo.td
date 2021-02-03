//===-- FalconInstrInfo.td - Falcon Instruction defs -------*- tablegen -*-===//
//
// Part of the LLVM fork for the Mirage project, under the Apache License v2.0
// with LLVM Exceptions. See https://llvm.org/LICENSE.txt for license
// information.
// SPDX-License-Identifier: Apache-2.0 with LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file describes the Falcon instructions in TableGen format.
//
//===----------------------------------------------------------------------===//

include "FalconInstrFormats.td"


/*
def ADDiu   : ArithLogicI<0x09, "addiu", add, simm16, immSExt16, CPURegs>;

/// Arithmetic and logical instructions with 2 register operands.
class ArithLogicI<bits<8> op, string instr_asm, SDNode OpNode, Operand Od, PatLeaf imm_type, RegisterClass RC> :
  FL<op, (outs GPROut:$ra), (ins RC:$rb, Od:$imm16), !strconcat(instr_asm, "\t$ra, $rb, $imm16"), [(set GPROut:$ra, (OpNode RC:$rb, imm_type:$imm16))], IIAlu>
{
  let isReMaterializable = 1;
}
*/
