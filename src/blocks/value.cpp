#include <blocks/value.h>

llvm::Value *ValueExpression::codegen(CompilerContext& nyacc_context, llvm::LLVMContext& context, llvm::IRBuilder<>& builder) const {
  return llvm::ConstantInt::get(context, llvm::APInt(/*nbits*/64, val_));
}