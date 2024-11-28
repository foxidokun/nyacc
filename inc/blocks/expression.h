#pragma once

#include <context.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Value.h>
#include <types.h>

class Expression {
public:
  virtual ~Expression() = default;
  virtual TypedValue codegen(CompilerContext &nyacc_context) const = 0;
};