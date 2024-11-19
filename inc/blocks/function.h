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
  Function(ValType rettype, std::string name, std::vector<std::unique_ptr<Statement>> content): rettype_(rettype), name_(std::move(name)), content_(std::move(content)) {};

  void codegen(CompilerContext& nyacc_context) const;

private:
  ValType rettype_;
  std::string name_;
  std::vector<std::unique_ptr<Statement>> content_;
};