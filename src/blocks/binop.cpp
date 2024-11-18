#include <blocks/binop.h>
#include <fmt/format.h>
#include <llvm/ADT/APInt.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Value.h>

llvm::Value *BinopExpression::codegen(llvm::LLVMContext& context, llvm::IRBuilder<>& builder) const {
  return nullptr;
}