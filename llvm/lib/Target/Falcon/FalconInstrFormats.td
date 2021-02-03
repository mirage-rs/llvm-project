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
// Base Falcon instruction definitions
//===----------------------------------------------------------------------===//

// A generic Falcon machine instruction.
class FalconInst<int size, dag outs, dag ins, string asmstr,
                 list<dag> pattern>
  : Instruction
{
  let Namespace = "Falcon";
  let DecoderNamespace = "Falcon";

  let Size = size;
  dag OutOperandList = outs;
  dag InOperandList = ins;
  let Pattern = pattern;
  let AsmString = asmstr;
}

// A 16-bit Falcon machine instruction.
class FalconInst16<dag outs, dag ins, string asmstr, list<dag> pattern>
  : FalconInst<2, outs, ins, asmstr, pattern>
{
  field bits<16> Inst;

  // SoftFail is a field the disassembler can use to provide a way for
  // instructions to not match without killing the whole decode process.
  // It is mainly used for ARM, but Tablegen expects this field to exist
  // or it fails to build the lookup tables for decoding instructions.
  field bits<16> SoftFail = 0;
}

// A 24-bit Falcon machine instruction.
class FalconInst24<dag outs, dag ins, string asmstr, list<dag> pattern>
  : FalconInst<3, outs, ins, asmstr, pattern>
{
  field bits<24> Inst;

  // SoftFail is a field the disassembler can use to provide a way for
  // instructions to not match without killing the whole decode process.
  // It is mainly used for ARM, but Tablegen expects this field to exist
  // or it fails to build the lookup tables for decoding instructions.
  field bits<24> SoftFail = 0;
}

// A 32-bit Falcon machine instruction.
class FalconInst32<dag outs, dag ins, string asmstr, list<dag> pattern>
  : FalconInst<4, outs, ins, asmstr, pattern>
{
  field bits<32> Inst;

  // SoftFail is a field the disassembler can use to provide a way for
  // instructions to not match without killing the whole decode process.
  // It is mainly used for ARM, but Tablegen expects this field to exist
  // or it fails to build the lookup tables for decoding instructions.
  field bits<32> SoftFail = 0;
}

// A 40-bit Falcon machine instruction.
class FalconInst40<dag outs, dag ins, string asmstr, list<dag> pattern>
  : FalconInst<5, outs, ins, asmstr, pattern>
{
  field bits<40> Inst;

  // SoftFail is a field the disassembler can use to provide a way for
  // instructions to not match without killing the whole decode process.
  // It is mainly used for ARM, but Tablegen expects this field to exist
  // or it fails to build the lookup tables for decoding instructions.
  field bits<40> SoftFail = 0;
}

// A pseudo instruction.
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
//
//===----------------------------------------------------------------------===//
