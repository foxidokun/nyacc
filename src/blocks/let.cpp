#include <blocks/let.h>

void LetStatement::codegen(CompilerContext& context) const {
  auto value = value_->codegen(context);
  auto variable = context.builder.CreateAlloca(llvm::Type::getInt64Ty(context.llvm_context), nullptr, name_);
  // Assign
  context.builder.CreateStore(value, variable);

  // Remeber
  context.insert_variable(name_, variable);
}