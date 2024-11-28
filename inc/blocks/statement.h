#pragma once

#include <context.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Value.h>

class Statement {
public:
  virtual ~Statement() = default;
  virtual void codegen(CompilerContext &nyacc_context) const = 0;
};