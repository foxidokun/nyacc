#pragma once

#include <llvm/IR/Value.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <context.h>

class Statement {
public:
  virtual ~Statement() = default;
  virtual void codegen(CompilerContext& nyacc_context) const = 0;
};