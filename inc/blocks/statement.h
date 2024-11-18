#pragma once

#include <llvm/IR/Value.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>

class Statement {
public:
  virtual ~Statement() = default;
  virtual void codegen(llvm::LLVMContext& context, llvm::IRBuilder<>& builder) const = 0;
};