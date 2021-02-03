//===-- FalconTargetInfo.h - Falcon Target Implementation -------*- C++ -*-===//
//
// Part of the LLVM fork for the Mirage project, under the Apache License v2.0
// with LLVM Exceptions. See https://llvm.org/LICENSE.txt for license
// information.
// SPDX-License-Identifier: Apache-2.0 with LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_TARGET_FALCON_TARGET_INFO_H
#define LLVM_TARGET_FALCON_TARGET_INFO_H

namespace llvm {

class Target;

Target &getTheFalconTarget();

} // end namespace llvm

#endif // LLVM_TARGET_FALCON_TARGET_INFO_H
