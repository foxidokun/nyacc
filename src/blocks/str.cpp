#include "context.h"
#include "types.h"
#include <blocks/str.h>
#include <llvm/ADT/APInt.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/Type.h>

TypedValue StrExpression::codegen(CompilerContext& context) const {
  auto i8_type = llvm::Type::getInt8Ty(context.llvm_context);

  std::vector<llvm::Constant *> data;
  for (auto ch: val_) {
    data.push_back(llvm::Constant::getIntegerValue(i8_type, llvm::APInt(8, ch)));
  }
  data.push_back(llvm::Constant::getIntegerValue(i8_type, llvm::APInt(8, 0)));

  auto i8_array = llvm::ArrayType::get(i8_type, data.size());
  auto const_value = llvm::ConstantArray::get(i8_array, data);

  // Freed by some llvm internals
  auto global_var = new llvm::GlobalVariable(context.module, i8_array, true, llvm::GlobalVariable::InternalLinkage, const_value);

  return {global_var, ValType{ValType::Kind::String, 0}};
}