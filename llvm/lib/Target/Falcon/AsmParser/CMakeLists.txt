add_llvm_component_library(LLVMFalconAsmParser
  FalconAsmParser.cpp

  LINK_COMPONENTS
  MC
  MCParser
  FalconDesc
  FalconInfo
  Support

  ADD_TO_COMPONENT
  Falcon
)
