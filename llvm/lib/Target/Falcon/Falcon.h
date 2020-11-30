//==-- Falcon.h - Top-level interface for Falcon representation --*- C++ -*-==//
//
// Part of the LLVM fork for the Mirage project, under the Apache License v2.0
// with LLVM Exceptions. See https://llvm.org/LICENSE.txt for license
// information.
// SPDX-License-Identifier: Apache-2.0 with LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in the LLVM
// Falcon back-end.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_TARGET_FALCON_H
#define LLVM_TARGET_FALCON_H

#include "llvm/CodeGen/SelectionDAGNodes.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class FalconTargetMachine;
class FunctionPass;

FunctionPass *createFalconISelDag(FalconTargetMachine &TM);

namespace Falcon {

/// Identifies all of the supported Falcon address spaces.
enum AddressSpace {
  /// The Falcon code segment in SRAM.
  ///
  /// The code segment uses virtual memory pages tracked by a reverse page
  /// table. Every page is 0x100 bytes in size and physical <-> virtual
  /// memory mapping is tracked by a hidden TLB which supports additional
  /// flags for pages. While virtual addresses can be up to 32 bits in size,
  /// physical addresses have not been observed to ever exceed a 16 bit range.
  IMem,
  /// The Falcon data segment in SRAM.
  ///
  /// The data segment has byte-oriented addressing and can be accessed in
  /// quantities of 8, 16 or 32 bits. Unaligned accesses are not supported and
  /// cause botched reads/writes. This address space is completely separate from
  /// IMem and thus a function can technically have the same address as a global
  /// variable.
  DMem,
  /// The Falcon I/O space.
  ///
  /// The I/O space consists of 32-bit I/O registers which are visible from
  /// Falcon and the host system. It consists of MCU control registers,
  /// interrupt and timer registers, IMem/DMem access windows, PFIFO
  /// communication registers and also engine-specific hardware registers the
  /// Falcon is supposed to control. Any kind of unaligned access is unsupported
  /// and the space exists completely separated from IMem and DMem.
  Io,
};

/// Checks if a given type is a pointer to program memory.
template <typename T> bool isProgramMemoryAddress(T *V) {
  return cast<PointerType>(V->getType())->getAddressSpace() == IMem;
}

/// Checks if the given memory operation is performed on program memory.
inline bool isProgramMemoryAccess(const MemSDNode *N) {
  auto V = N->getMemOperand()->getValue();

  return (V != nullptr) ? isProgramMemoryAddress(V) : false;
}

} // end namespace Falcon

} // end namespace llvm

#endif // LLVM_TARGET_FALCON_H
