#include <blocks/func_call.h>
#include <fmt/format.h>
#include <types.h>
#include <vector>

TypedValue FuncCallExpression::codegen(CompilerContext &context) const {
  auto func_type = context.get_function_type(name_);
  if (!func_type) {
    throw NyaccError(fmt::format("Unknown func {}", name_));
  }

  auto func = context.module.getFunction(name_);
  assert(func);

  std::vector<llvm::Value *> computed_args;
  for (auto [arg, dest_type] : llvm::zip(args_, func_type->second)) {
    auto argval = arg->codegen(context);
    argval = cast(context, argval, dest_type);
    computed_args.push_back(argval.val);
  }

  auto res = context.builder.CreateCall(func, computed_args);
  return {res, func_type->first};
}