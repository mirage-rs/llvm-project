add_llvm_component_library(LLVMFalconDisassembler
  FalconDisassembler.cpp

  LINK_COMPONENTS
  MCDisassembler
  FalconInfo
  Support

  ADD_TO_COMPONENT
  Falcon
)
