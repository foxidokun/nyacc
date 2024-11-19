#include <blocks/assig.h>
#include <fmt/base.h>

void AssigStatement::codegen(CompilerContext &context) const {
  auto var = context.get_variable(name_);
  if (!var.val) {
    fmt::println(stderr, "Unknown variable {}", name_);
    exit(1);
  }

  auto value = value_->codegen(context);
  auto casted_val = cast(context, value, var.type);

  context.builder.CreateStore(casted_val.val, var.val);
}