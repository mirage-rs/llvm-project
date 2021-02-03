add_llvm_component_library(LLVMFalconDesc
  FalconMCTargetDesc.cpp
)

add_dependencies(LLVMFalconDesc FalconCommonTableGen)
