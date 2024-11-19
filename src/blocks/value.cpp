#include "context.h"
#include "types.h"
#include <blocks/value.h>

TypedValue ValueExpression::codegen(CompilerContext& context) const {
  llvm::Value *inter;
  if (kind_ == ValType::Kind::Int) {
    inter = llvm::ConstantInt::get(context.llvm_context, llvm::APInt(/*nbits*/64, std::get<int64_t>(val_)));
  } else {
    inter = llvm::ConstantFP::get(context.llvm_context, llvm::APFloat(std::get<double>(val_)));
  }

  return {inter, ValType(kind_, 64)};
}