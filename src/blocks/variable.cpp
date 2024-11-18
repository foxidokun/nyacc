#include <blocks/variable.h>
#include <fmt/base.h>

llvm::Value *VariableExpression::codegen(CompilerContext& nyacc_context, llvm::LLVMContext& context, llvm::IRBuilder<>& builder) const {
  auto res = nyacc_context.get_variable(name_);
  if (!res) {
    fmt::println(stderr, "Unknown variable {}", name_);
    exit(1);
  }
  return res;
}