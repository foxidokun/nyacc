#include <blocks/function.h>

void Function::codegen(CompilerContext& nyacc_context, llvm::LLVMContext& context, llvm::IRBuilder<>& builder, llvm::Module& module) const  {
  auto *function_type =
      llvm::FunctionType::get(llvm::Type::getInt64Ty(context), std::vector<llvm::Type *>(), false);
  
  auto *function =
      llvm::Function::Create(function_type, llvm::Function::ExternalLinkage, "main", module);
  auto *entry_block = llvm::BasicBlock::Create(context, "entry", function);
  builder.SetInsertPoint(entry_block);
  
  for (auto &statement: content_) {
    statement->codegen(nyacc_context, context, builder);
  }
}