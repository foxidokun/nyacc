#pragma once

#include "blocks/function.h"
#include <llvm/IR/Value.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <memory>
#include <vector>

class Program {
public:
  Program(std::vector<std::unique_ptr<Function>> content): content_(std::move(content)) {};

  void codegen(CompilerContext& nyacc_context) const;

private:
  std::vector<std::unique_ptr<Function>> content_;
};