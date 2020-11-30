set(LLVM_TARGET_DEFINITIONS Falcon.td)

tablegen(LLVM FalconGenAsmMatcher.inc -gen-asm-matcher)
tablegen(LLVM FalconGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM FalconGenCallingConv.inc -gen-callingconv)
tablegen(LLVM FalconGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM FalconGenDisassemblerTables.inc -gen-disassembler)
tablegen(LLVM FalconGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM FalconGenMCCodeEmitter.inc -gen-emitter)
tablegen(LLVM FalconGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM FalconGenSubtargetInfo.inc -gen-subtarget)

add_public_tablegen_target(FalconCommonTableGen)

add_llvm_target(FalconCodeGen
  # TODO
)

#add_subdirectory(AsmParser)
#add_subdirectory(Disassembler)
#add_subdirectory(MCTargetDesc)
#add_subdirectory(TargetInfo)
