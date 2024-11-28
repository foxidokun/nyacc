#include <blocks/common.h>
#include <types.h>

static llvm::Value *const_zero_i64(CompilerContext &context) {
  return llvm::ConstantInt::get(llvm::Type::getInt64Ty(context.llvm_context),
                                llvm::APInt(64, 0));
}

TypedValue boolify(CompilerContext &context, TypedValue val) {
  val = cast(context, val, ValType{ValType::Kind::Int, 64});
  auto cmp_res = context.builder.CreateICmpNE(val.val, const_zero_i64(context));

  return {cmp_res, ValType{ValType::Kind::Int, 1}};
}
