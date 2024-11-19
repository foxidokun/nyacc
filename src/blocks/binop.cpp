#include <blocks/binop.h>
#include <fmt/format.h>
#include <llvm/ADT/APInt.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Value.h>

llvm::Value *BinopExpression::codegen(CompilerContext& context) const {
  auto lhs = lhs_->codegen(context);
  auto rhs = rhs_->codegen(context);

  switch (type_) {
    case OpSign::Minus: return context.builder.CreateSub(lhs,rhs);
    case OpSign::Plus: return context.builder.CreateAdd(lhs,rhs);
    case OpSign::Mul: return context.builder.CreateMul(lhs,rhs);
    case OpSign::Div: return context.builder.CreateSDiv(lhs,rhs); // Signed div
    default:
      exit(1);
  }
}