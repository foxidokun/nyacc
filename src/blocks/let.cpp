#include <blocks/let.h>

void LetStatement::codegen(CompilerContext &context) const {
  auto value = value_->codegen(context);

  // Create alloca in the entry block of function
  auto *parentFunction = context.builder.GetInsertBlock()->getParent();
  // create temp builder to point to start of function
  llvm::IRBuilder<> entry_builder(&(parentFunction->getEntryBlock()),
                               parentFunction->getEntryBlock().begin());

  auto casted_val = cast(context, value, type_);

  auto variable = entry_builder.CreateAlloca(type_.llvm_type(context.llvm_context), nullptr, name_);
  // Assign
  context.builder.CreateStore(casted_val.val, variable);

  // Remeber after assigment
  context.insert_variable(name_, {variable, type_});
}