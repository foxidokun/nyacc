#include <blocks/value.h>

llvm::Value *ValueExpression::codegen(CompilerContext& context) const {
  return llvm::ConstantInt::get(context.llvm_context, llvm::APInt(/*nbits*/64, val_));
}