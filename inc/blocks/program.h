#pragma once

#include <blocks/statement.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <memory>
#include <vector>

class Program {
public:
  Program(std::vector<std::unique_ptr<Statement>> content): content_(std::move(content)) {};

  void codegen(CompilerContext& nyacc_context) const;

private:
  std::vector<std::unique_ptr<Statement>> content_;
};