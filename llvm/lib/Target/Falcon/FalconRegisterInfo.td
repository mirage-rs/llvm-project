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
class FalconReg<bits<16> Enc,
                string name,
                list<Register> subregs = [],
                list<string> altNames = []>
  : RegisterWithSubRegs<name, subregs>
{
  let HWEncoding = Enc;
  let Namespace = "Falcon";
  let SubRegs = subregs;
  let AltNames = altNames;
}
