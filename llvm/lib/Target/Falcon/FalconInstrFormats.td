//===-- FalconInstrInfo.td - Falcon Instruction Formats ----*- tablegen -*-===//
//
// Part of the LLVM fork for the Mirage project, under the Apache License v2.0
// with LLVM Exceptions. See https://llvm.org/LICENSE.txt for license
// information.
// SPDX-License-Identifier: Apache-2.0 with LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Falcon Instruction Format Definitions.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Basic Falcon instruction definition
//===----------------------------------------------------------------------===//

/// A generic Falcon instruction.
class FalconInst<int size, dag outs, dag ins, string asmstr,
                 list<dag> pattern> : Instruction {
  let Namespace = "Falcon";

  dag OutOperandList = outs;
  dag InOperandList = ins;
  let Size = size;
  let Pattern = pattern;
  let AsmString = asmstr;
}

/// A 16-bit Falcon instruction.
class FalconInst16<dag outs, dag ins, string asmstr, list<dag> pattern>
  : FalconInst<2, outs, ins, asmstr, pattern>
{
  field bits<16> Inst;

  field bits<16> SoftFail = 0;
}

/// A 24-bit Falcon instruction.
class FalconInst24<dag outs, dag ins, string asmstr, list<dag> pattern>
  : FalconInst<3, outs, ins, asmstr, pattern>
{
  field bits<24> Inst;

  field bits<24> SoftFail = 0;
}

/// A 32-bit Falcon instruction.
class FalconInst32<dag outs, dag ins, string asmstr, list<dag> pattern>
  : FalconInst<4, outs, ins, asmstr, pattern>
{
  field bits<32> Inst;

  field bits<32> SoftFail = 0;
}

/// A 40-bit Falcon instruction.
class FalconInst40<dag outs, dag ins, string asmstr, list<dag> pattern>
  : FalconInst<5, outs, ins, asmstr, pattern>
{
  field bits<40> Inst;

  field bits<40> SoftFail = 0;
}

// A class for pseudo instructions.
//
// Pseudo instructions are not real Falcon instructions. The DAG
// stores pseudo instructions which are replaced by real Falcon
// instructions by FalconExpandPseudoInsts.cpp.
//
// The SCP crypto instructions (cenc, cdec, ...) are all defined
// as pseudo instructions. In FalconExpandPseudoInsts.cpp, the
// instruction is then replaced by the real ccmd instruction with
// the corresponding SCP opcode.
class Pseudo<dag outs, dag ins, string asmstr, list<dag> pattern>
  : FalconInst32<outs, ins, asmstr, pattern>
{
  let isPseudo = 1;
  let isCodeGenOnly = 1;
}

//===----------------------------------------------------------------------===//
// Falcon Instruction formats
//===----------------------------------------------------------------------===//
//
// The forms are named after the operands they take:
//
//   S            : sized form; high 2 bits of opcode select operation size
//   R            : a read-only register operand
//   W            : a write-only register operand
//   M            : a read-modify-write register operand
//   I            : an immediate operand (8-bit, 16-bit, 24-bit, 32-bit)
//   N            : no operands
//===----------------------------------------------------------------------===//

/// Sized instructions which take two registers and an i8 immediate as operands.
///
/// This form is used for arithmetic instructions and the LD instruction.
class FalconInstSWRI8<bits<2> size, bits<2> a, bits<4> b, dag outs,
                      dag ins, string asmstr, list<dag> pattern>
  : FalconInst24<outs, ins, asmstr, pattern>
{
  bits<4> R1;
  bits<4> R2;
  bits<8> I8;
  
  let Inst{23-16} = I8;
  let Inst{15-12} = R1;
  let Inst{11-8} = R2;

  let Inst{7-6} = size;
  let Inst{5-4} = a;
  let Inst{3-0} = b;
}

/// Unsized instructions which take a 24-bit immediate as their single operand.
///
/// Introduced in Falcon v4, used for long calls and long branches.
class FalconInstI24<bits<8> opcode, dag outs, dag ins, string asmstr,
                    list<dag> pattern>
  : FalconInst32<outs, ins, asmstr, pattern>
{
  bits<24> I24;

  let Inst{7-0} = opcode;
  let Inst{31-8} = I24;
}
