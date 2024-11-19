#include <blocks/func_call.h>
#include <fmt/base.h>
#include <vector>

TypedValue FuncCallExpression::codegen(CompilerContext& context) const {
  auto ret_type = context.get_func_ret(name_);
  if (!ret_type) {
    fmt::println("Unknown func {}", name_);
    exit(1);
  }

  auto func = context.module.getFunction(name_);
  assert(func);

  std::vector<llvm::Value *> computed_args;
  for (auto& arg: args_) {
    auto argval = arg->codegen(context);
    computed_args.push_back(argval.val);
  }

  auto res = context.builder.CreateCall(func, computed_args);
  return {res, ret_type.value()};
}