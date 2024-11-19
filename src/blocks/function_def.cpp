#include <blocks/function_def.h>

void FunctionDef::codegen(CompilerContext& context) const  {
  // Convert args to llvm type
  std::vector<llvm::Type *> llvm_args;
  for (auto& argument: args_) {
    llvm_args.emplace_back(argument.first.llvm_type(context.llvm_context));
  }

  auto *function_type =
      llvm::FunctionType::get(rettype_.llvm_type(context.llvm_context), llvm_args, false);
  
  auto *function =
      llvm::Function::Create(function_type, llvm::Function::ExternalLinkage, name_, context.module);
}