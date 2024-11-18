#include <blocks/let.h>

void LetStatement::codegen(CompilerContext& nyacc_context, llvm::LLVMContext& context, llvm::IRBuilder<>& builder) const {
  auto value = value_->codegen(nyacc_context, context, builder);
  auto variable = builder.CreateAlloca(llvm::Type::getInt64Ty(context), nullptr, name_);
  // Assign
  builder.CreateStore(value, variable);

  // Remeber
  nyacc_context.insert_variable(name_, variable);
}