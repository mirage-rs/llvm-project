//===-- FalconMCAsmInfo.cpp - Falcon asm properties -----------------------===//
//
// Part of the LLVM fork for the Mirage project, under the Apache License v2.0
// with LLVM Exceptions. See https://llvm.org/LICENSE.txt for license
// information.
// SPDX-License-Identifier: Apache-2.0 with LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the declarations of the FalconMCAsmInfo properties.
//
//===----------------------------------------------------------------------===//

#include "FalconMCAsmInfo.h"

#include "llvm/ADT/Triple.h"

namespace llvm {

FalconMCAsmInfo::FalconMCAsmInfo(const Triple &TT,
                                 const MCTargetOptions &Options) {
  CommentString = "//";
  PrivateGlobalPrefix = ".L";
  PrivateLabelPrefix = ".L";
  SupportsDebugInformation = true;
  UseIntegratedAssembler = true;
}

} // end namespace llvm
