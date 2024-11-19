#include "context.h"
#include "types.h"
#include <blocks/value.h>

TypedValue ValueExpression::codegen(CompilerContext& context) const {
  return {llvm::ConstantInt::get(context.llvm_context, llvm::APInt(/*nbits*/64, val_)), ValType(ValType::Kind::Int, 64)};
}