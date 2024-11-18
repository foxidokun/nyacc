#pragma once

#include <llvm/IR/Value.h>
#include <string>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>

class Expression {
public:
  virtual std::string format() const = 0;
  virtual ~Expression() = default;
  virtual llvm::Value* codegen(llvm::LLVMContext& context, llvm::IRBuilder<>& builder) const = 0;
};