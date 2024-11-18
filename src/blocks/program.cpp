#include <blocks/program.h>

void Program::codegen(CompilerContext& nyacc_context, llvm::LLVMContext& context, llvm::IRBuilder<>& builder, llvm::Module& module) const  {
  for (auto &function: content_) {
    function->codegen(nyacc_context, context, builder, module);
  }
}