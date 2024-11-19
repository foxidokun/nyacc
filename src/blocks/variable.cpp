#include <blocks/variable.h>
#include <fmt/format.h>
#include <llvm/IR/Type.h>

llvm::Value *VariableExpression::codegen(CompilerContext& context) const {
  auto var = context.get_variable(name_);
  if (!var) {
    fmt::println(stderr, "Unknown variable {}", name_);
    exit(1);
  }

  // Currently all variables are local => alloca-ted
  // Probably need to change this for global const strings
  auto alloca_inst = static_cast<llvm::AllocaInst *>(var);
  var = context.builder.CreateLoad(alloca_inst->getAllocatedType(), var, fmt::format("loaded_{}", name_));

  return var;
}