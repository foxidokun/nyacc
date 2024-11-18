#include <blocks/variable.h>

llvm::Value *VariableExpression::codegen(CompilerContext& nyacc_context, llvm::LLVMContext& context, llvm::IRBuilder<>& builder) const {
  return nyacc_context.get_variable(name_);
}