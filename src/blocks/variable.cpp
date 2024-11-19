#include <blocks/variable.h>
#include <fmt/format.h>
#include <llvm/IR/Type.h>

llvm::Value *VariableExpression::codegen(CompilerContext& context) const {
  auto res = context.get_variable(name_);
  if (!res) {
    fmt::println(stderr, "Unknown variable {}", name_);
    exit(1);
  }

  res = context.builder.CreateLoad(llvm::Type::getInt64Ty(context.llvm_context), res, fmt::format("loaded_{}", name_));

  return res;
}