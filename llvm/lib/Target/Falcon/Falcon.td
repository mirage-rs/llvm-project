//===-- Falcon.td - Describe the Falcon Target Machine ----*- tablegen -*-===//
//
// Part of the LLVM fork for the Mirage project, under the Apache License v2.0
// with LLVM Exceptions. See https://llvm.org/LICENSE.txt for license
// information.
// SPDX-License-Identifier: Apache-2.0 with LLVM-exception
//
//===---------------------------------------------------------------------===//
// This is the top level entry point for the Falcon target.
//===---------------------------------------------------------------------===//

//===---------------------------------------------------------------------===//
// Target-independent interfaces which we are implementing
//===---------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// Falcon Subtarget features.
//===----------------------------------------------------------------------===//

def FeatureScp
  : SubtargetFeature<"scp", "HasSCP", "true",
                     "Is Secure CoProcessor available">;

//===---------------------------------------------------------------------===//
// Target Declaration
//===---------------------------------------------------------------------===//

def Falcon : Target {
  // TODO
}
