#include <blocks/function.h>
#include <blocks/function_def.h>

void Function::codegen(CompilerContext &context) const {
  context.enter_visibility_block();
  context.enter_function(name_);

  // Lookup function
  auto *function = context.module.getFunction(name_);

  if (!function) {
    // Create temp definition
    FunctionDef temporary_def(rettype_, name_, args_);
    temporary_def.codegen(context);
    function = context.module.getFunction(name_);
  }

  auto *entry_block =
      llvm::BasicBlock::Create(context.llvm_context, "entry", function);
  context.builder.SetInsertPoint(entry_block);

  // Generate allocates for parameters
  for (auto [llvm_arg, arg] : llvm::zip(function->args(), args_)) {
    // Allocate
    auto val =
        context.builder.CreateAlloca(llvm_arg.getType(), nullptr, arg.second);

    // Store
    context.builder.CreateStore(&llvm_arg, val);

    // Remeber
    context.insert_variable(arg.second, {val, arg.first});
  }

  for (auto &statement : content_) {
    statement->codegen(context);
  }

  context.exit_visibility_block();
}