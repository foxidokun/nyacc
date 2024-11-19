#include <blocks/function.h>

void Function::codegen(CompilerContext& context) const  {
  context.enter_visibility_block();

  auto *function_type =
      llvm::FunctionType::get(llvm::Type::getInt64Ty(context.llvm_context), std::vector<llvm::Type *>(), false);
  
  auto *function =
      llvm::Function::Create(function_type, llvm::Function::ExternalLinkage, name_, context.module);
  auto *entry_block = llvm::BasicBlock::Create(context.llvm_context, "entry", function);
  context.builder.SetInsertPoint(entry_block);

  for (auto &statement: content_) {
    statement->codegen(context);
  }

  context.exit_visibility_block();
}