#include <blocks/function.h>

void Function::codegen(CompilerContext& context) const  {
  context.enter_visibility_block();

  // Lookup function
  auto *function = context.module.getFunction(name_);

  if (!function) {
    // Convert args to llvm type
    std::vector<llvm::Type *> llvm_args;
    for (auto& argument: args_) {
      llvm_args.emplace_back(argument.first.llvm_type(context.llvm_context));
    }

    auto *function_type =
        llvm::FunctionType::get(rettype_.llvm_type(context.llvm_context), llvm_args, false);
    
    function =
        llvm::Function::Create(function_type, llvm::Function::ExternalLinkage, name_, context.module);
  }
  
  auto *entry_block = llvm::BasicBlock::Create(context.llvm_context, "entry", function);
  context.builder.SetInsertPoint(entry_block);

  // Generate allocates for parameters
  for (auto [llvm_arg, arg]: llvm::zip(function->args(), args_)) {
    // Allocate
    auto val = context.builder.CreateAlloca(llvm_arg.getType(), nullptr, arg.second);
    
    // Store 
    context.builder.CreateStore(&llvm_arg, val);

    // Remeber
    context.insert_variable(arg.second, {val, arg.first});
  }

  for (auto &statement: content_) {
    statement->codegen(context);
  }

  context.exit_visibility_block();
}