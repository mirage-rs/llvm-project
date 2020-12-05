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
//  Special-purpose registers
//===----------------------------------------------------------------------===//

// A 32-bit special-purpose register.
class FalconSpr<bits<16> Enc, string name> : FalconReg<name> {
  let HWEncoding = Enc;
}

// Holds the address of interrupt vector 0.
def IV0  : FalconSpr<0,  "iv0">,  DwarfRegNum<[16]>;
// Holds the address of interrupt vector 1.
def IV1  : FalconSpr<1,  "iv1">,  DwarfRegNum<[17]>;
// Holds the address of interrupt vector 2. Officially marked as "UNDEFINED".
def IV2  : FalconSpr<2,  "iv2">,  DwarfRegNum<[18]>;
// Holds the address of the exception vector.
def EV   : FalconSpr<3,  "ev">,   DwarfRegNum<[19]>;
// Holds the current stack pointer.
def SP   : FalconSpr<4,  "sp">,   DwarfRegNum<[20]>;
// Holds the current program counter.
def PC   : FalconSpr<5,  "pc">,   DwarfRegNum<[21]>;
// Holds the external base address for IMEM transfers.
def IMB  : FalconSpr<6,  "imb">,  DwarfRegNum<[22]>;
// Holds the external base address for DMEM transfers.
def DMB  : FalconSpr<7,  "dmb">,  DwarfRegNum<[23]>;
// Holds various CPU flag bits.
def CSW  : FalconSpr<8,  "csw">,  DwarfRegNum<[24]>;
// Holds configuration bits for the SCP DMA override functionality.
def CCR  : FalconSpr<9,  "ccr">,  DwarfRegNum<[25]>;
// Holds configuration bits for the SCP authentication process.
def SCP  : FalconSpr<10, "sec">,  DwarfRegNum<[26]>;
// Holds configuration bits for the CTXDMA ports.
def CTX  : FalconSpr<11, "ctx">,  DwarfRegNum<[27]>;
// Holds information on raised exceptions.
def EXCI : FalconSpr<12, "exci">, DwarfRegNum<[28]>;
// Unknown. Officially marked as "RESERVED".
def SEC1 : FalconSpr<13, "sec1">, DwarfRegNum<[29]>;
// Unknown. Officially marked as "RESERVED".
def IMB1 : FalconSpr<14, "imb1">, DwarfRegNum<[30]>;
// Unknown. Officially marked as "RESERVED".
def DMB1 : FalconSpr<15, "dmb1">, DwarfRegNum<[31]>;

//===----------------------------------------------------------------------===//
//  Secure Co-Processor crypto registers
//===----------------------------------------------------------------------===//

// A 133-bit SCP crypto register.
// The first 128 bits store the crypto data for AES operations.
// The last 5 bits store an ACL value regulating access to the register.
class FalconCr<bits<16> Enc, string name> : FalconReg<name> {
  let HWEncoding = Enc;
}

// Define the 8 crypto registers.
foreach I = 0-7 in {
  def C#I : FalconCr<I, "c"#I>, DwarfRegNum<[32 + I]>;
}

//===----------------------------------------------------------------------===//
// Register Classes
//===----------------------------------------------------------------------===//

// Allocate all the GPRs and their subregisters.
def GPRB : RegisterClass<"Falcon", [i8],  8 , (add (sequence "R%uB", 0, 15))>;
def GPRH : RegisterClass<"Falcon", [i16], 16, (add (sequence "R%uH", 0, 15))>;
def GPR  : RegisterClass<"Falcon", [i32], 32, (add (sequence "R%u", 0, 15))>;

// Allocate all the SPRs that can be read from using the MOV opcode.
def SPRR : RegisterClass<"Falcon", [i32], 32, (add
  // Interrupt and Exception handling registers
  IV0, IV1, IV2, EV, EXCI,
  // Execution registers
  SP, PC,
  // DMA configuration registers
  IMB, DMB, CTX,
  // CPU flags register
  CSW,
  // SCP security feature registers
  CCR, SCP,
  // Reserved/Unknown registers
  SEC1, IMB1, DMB1)>;

// Allocate all the SPRs that can be written to using the MOV opcode.
def SPRW : RegisterClass<"Falcon", [i32], 32, (add
  // Interrupt and Exception handling registers
  IV0, IV1, IV2, EV, EXCI,
  // Execution registers
  SP,
  // DMA configuration registers
  IMB, DMB, CTX,
  // CPU flags register
  CSW,
  // SCP security feature registers
  SCP,
  // Reserved/Unknown registers
  SEC1, IMB1, DMB1)>;

// Allocate all the SCP crypto registers.
def CR : RegisterClass<"Falcon", [i133], 133, (add (sequence "C%u", 0, 7))>;
