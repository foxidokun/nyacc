#include <expressions/sum.h>
#include <fmt/format.h>
#include <llvm/ADT/APInt.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Value.h>

std::string SumExpression::format() const {
  return fmt::format("{} + {}", lhs_, rhs_);
}

llvm::Value *SumExpression::codegen(llvm::LLVMContext& context, llvm::IRBuilder<>& builder) const {
  auto lhs = llvm::ConstantInt::get(context, llvm::APInt(/*nbits*/64, lhs_));
  auto rhs = llvm::ConstantInt::get(context, llvm::APInt(/*nbits*/64, rhs_));

  return builder.CreateAdd(lhs,rhs);
}