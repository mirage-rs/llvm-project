//===-- FalconMCTargetDesc.h - Falcon Target Descriptions -------*- C++ -*-===//
//
// Part of the LLVM fork for the Mirage project, under the Apache License v2.0
// with LLVM Exceptions. See https://llvm.org/LICENSE.txt for license
// information.
// SPDX-License-Identifier: Apache-2.0 with LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides Falcon-specific target descriptions.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_TARGET_FALCON_MCTARGET_DESC_H
#define LLVM_TARGET_FALCON_MCTARGET_DESC_H

#include "llvm/Support/DataTypes.h"

namespace llvm {

class Target;
class Triple;

// TODO

} // end namespace llvm

#define GET_REGINFO_ENUM
#include "FalconGenRegisterInfo.inc"

#define GET_INSTRINFO_ENUM
#include "FalconGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "FalconGenSubtargetInfo.inc"

#endif // LLVM_TARGET_FALCON_MCTARGET_DESC_H
