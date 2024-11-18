#pragma once

#include "blocks/statement.h"
#include <llvm/IR/Value.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <memory>
#include <string>
#include <vector>

class Function {
public:
  Function(std::string name, std::vector<std::unique_ptr<Statement>> content): name_(std::move(name)), content_(std::move(content)) {};

  void codegen(CompilerContext& nyacc_context, llvm::LLVMContext& context, llvm::IRBuilder<>& builder, llvm::Module& module) const;

private:
  std::string name_;
  std::vector<std::unique_ptr<Statement>> content_;
};