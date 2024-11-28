#include <blocks/assig.h>
#include <context.h>
#include <fmt/base.h>
#include <fmt/format.h>

void AssigStatement::codegen(CompilerContext &context) const {
  auto var = context.get_variable(name_);
  if (!var.val) {
    throw NyaccError(fmt::format("Unknown variable {}", name_));
  }

  auto value = value_->codegen(context);
  auto casted_val = cast(context, value, var.type);

  context.builder.CreateStore(casted_val.val, var.val);
}