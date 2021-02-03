set(LLVM_TARGET_DEFINITIONS Falcon.td)

tablegen(LLVM FalconGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM FalconGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM FalconGenSubtargetInfo.inc -gen-subtarget)

add_public_tablegen_target(FalconCommonTableGen)

add_llvm_target(FalconCodeGen
  FalconTargetMachine.cpp
)

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
