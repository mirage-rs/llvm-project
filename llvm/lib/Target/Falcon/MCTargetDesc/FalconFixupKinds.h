//===-- FalconFixupKinds.h - Falcon-specific Fixup Entries ------*- C++ -*-===//
//
// Part of the LLVM fork for the Mirage project, under the Apache License v2.0
// with LLVM Exceptions. See https://llvm.org/LICENSE.txt for license
// information.
// SPDX-License-Identifier: Apache-2.0 with LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_TARGET_FALCON_FIXUP_KINDS_H
#define LLVM_TARGET_FALCON_FIXUP_KINDS_H

#include "llvm/MC/MCFixup.h"

namespace llvm {
namespace Falcon {

/// The set of supported fixups.
///
/// Although most of the current fixup types reflect a unique relocation
/// one can have multiple fixup types for a given relocation and thus need
/// to be uniquely named.
///
/// \note This table *must* be in the same order of
///       MCFixupKindInfo Infos[Falcon::NumTargetFixupKinds]
///       in `FalconAsmBackend.cpp`.
enum Fixups {

  // Marker
  LastTargetFixupKind,
  NumTargetFixupKinds = LastTargetFixupKind - FirstTargetFixupKind,
};

namespace fixups {

// TODO

} // end namespace fixups

} // end namespace Falcon
} // end namespace llvm

#endif // LLVM_TARGET_FALCON_FIXUP_KINDS_H
