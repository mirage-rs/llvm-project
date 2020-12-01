//===-- FalconRegisterInfo.td - Falcon Register defs -------*- tablegen -*-===//
//
// Part of the LLVM fork for the Mirage project, under the Apache License v2.0
// with LLVM Exceptions. See https://llvm.org/LICENSE.txt for license
// information.
// SPDX-License-Identifier: Apache-2.0 with LLVM-exception
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Declarations that describe the Falcon register file
//===----------------------------------------------------------------------===//

// Generic Falcon register definition.
class FalconReg<string name> : Register<name> {
  let Namespace = "Falcon";
}

// Generic Falcon register definition with subregisters.
class FalconRegWithSubregs<string name, list<Register> subregs>
  : RegisterWithSubRegs<name, subregs>
{
  let Namespace = "Falcon";
}

let Namespace = "Falcon" in {
  // The low 8 bits of a register.
  def subreg_l8  : SubRegIndex<8, 0>;
  // The low 16 bits of a register.
  def subreg_l16 : SubRegIndex<16, 0>;
}

//===----------------------------------------------------------------------===//
//  General-purpose registers
//===----------------------------------------------------------------------===//

// Lower 8 bits of a general-purpose register.
class FalconGpr8<bits<16> Enc, string name> : FalconReg<name> {
  let HWEncoding = Enc;
}

// Lower 16 bits of a general-purpose register.
class FalconGpr16<bits<16> Enc, string name, FalconGpr8 low>
  : FalconRegWithSubregs<name, [low]>
{
  let HWEncoding = Enc;
  let SubRegIndices = [subreg_l8];
}

// A 32-bit general-purpose register.
class FalconGpr32<bits<16> Enc, string name, FalconGpr16 low>
  : FalconRegWithSubregs<name, [low]>
{
  let HWEncoding = Enc;
  let SubRegIndices = [subreg_l16];
}

// Define the 16 GPRs along with subregisters for their low
// 8 and 16 bits as needed by sized instruction opcodes.
foreach I = 0-15 in {
  def R#I#B : FalconGpr8<I, "r"#I#"b">, DwarfRegNum<[I]>;
  def R#I#H : FalconGpr16<I, "r"#I#"h", !cast<FalconGpr8>("R"#I#"B")>,
              DwarfRegNum<[I]>;
  def R#I   : FalconGpr32<I, "r"#I, !cast<FalconGpr16>("R"#I#"H")>,
              DwarfRegNum<[I]>;
}

//===----------------------------------------------------------------------===//
// Register Classes
//===----------------------------------------------------------------------===//

// Allocate all the GPRs and their subregisters.
def GPRB : RegisterClass<"Falcon", [i8],  8 , (add (sequence "R%uB", 0, 15))>;
def GPRH : RegisterClass<"Falcon", [i16], 16, (add (sequence "R%uH", 0, 15))>;
def GPR  : RegisterClass<"Falcon", [i32], 32, (add (sequence "R%u", 0, 15))>;
