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
