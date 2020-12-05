//===-- FalconMCAsmInfo.h - Falcon asm properties ---------------*- C++ -*-===//
//
// Part of the LLVM fork for the Mirage project, under the Apache License v2.0
// with LLVM Exceptions. See https://llvm.org/LICENSE.txt for license
// information.
// SPDX-License-Identifier: Apache-2.0 with LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the FalconMCAsmInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_TARGET_FALCON_ASM_INFO_H
#define LLVM_TARGET_FALCON_ASM_INFO_H

#include "llvm/MC/MCAsmInfo.h"

namespace llvm {

class Triple;

/// Specifies the format of Falcon assembly files.
class FalconMCAsmInfo : public MCAsmInfo {
public:
  explicit FalconMCAsmInfo(const Triple &TT, const MCTargetOptions &Options);
};

} // end namespace llvm

#endif // LLVM_TARGET_FALCON_ASM_INFO_H
