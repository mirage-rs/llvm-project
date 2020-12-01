//===-- FalconMachineFunctionInfo.cpp - Falcon machine function info ------===//
//
// Part of the LLVM fork for the Mirage project, under the Apache License v2.0
// with LLVM Exceptions. See https://llvm.org/LICENSE.txt for license
// information.
// SPDX-License-Identifier: Apache-2.0 with LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "FalconMachineFunctionInfo.h"

namespace llvm {

// Pin VTable to this file.
void FalconMachineFunctionInfo::anchor() {}

} // end namespace llvm
