#include "context.h"
#include <blocks/variable.h>
#include <fmt/format.h>
#include <llvm/IR/Type.h>

TypedValue VariableExpression::codegen(CompilerContext& context) const {
  auto var = context.get_variable(name_);
  if (!var.val) {
    fmt::println(stderr, "Unknown variable {}", name_);
    exit(1);
  }

  // Currently all variables are local => alloca-ted
  // Probably need to change this for global const strings
  var.val = context.builder.CreateLoad(var.type.llvm_type(context.llvm_context), var.val, fmt::format("loaded_{}", name_));

  return var;
}