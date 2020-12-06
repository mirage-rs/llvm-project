//===-- FalconInstrInfo.cpp - Falcon Instruction Information --------------===//
//
// Part of the LLVM fork for the Mirage project, under the Apache License v2.0
// with LLVM Exceptions. See https://llvm.org/LICENSE.txt for license
// information.
// SPDX-License-Identifier: Apache-2.0 with LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the Falcon implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

#include "FalconInstrInfo.h"

#define GET_INSTRINFO_CTOR_DTOR
#include "FalconGenInstrInfo.inc"

namespace llvm {

FalconInstrInfo::FalconInstrInfo()
    : FalconGenInstrInfo(Falcon::ADJCALLSTACKDOWN, Falcon::ADJCALLSTACKUP),
      RI() {}

} // end namespace llvm
