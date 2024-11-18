#include <blocks/return.h>

void ReturnStatement::codegen(CompilerContext& nyacc_context, llvm::LLVMContext& context, llvm::IRBuilder<>& builder) const {
  auto retval = value_->codegen(nyacc_context, context, builder);
  builder.CreateRet(retval);
}