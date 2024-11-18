#include <blocks/binop.h>
#include <fmt/format.h>
#include <llvm/ADT/APInt.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Value.h>

llvm::Value *BinopExpression::codegen(CompilerContext& nyacc_context, llvm::LLVMContext& context, llvm::IRBuilder<>& builder) const {
  auto lhs = lhs_->codegen(nyacc_context, context, builder);
  auto rhs = rhs_->codegen(nyacc_context, context, builder);

  switch (type_) {
    case OpSign::Minus: return builder.CreateSub(lhs,rhs);
    case OpSign::Plus: return builder.CreateAdd(lhs,rhs);
    case OpSign::Mul: return builder.CreateMul(lhs,rhs);
    case OpSign::Div: return builder.CreateSDiv(lhs,rhs); // Signed div
    default:
      exit(1);
  }
}