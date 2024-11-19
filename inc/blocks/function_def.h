#pragma once

#include "blocks/statement.h"
#include <llvm/IR/Value.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <string>
#include <vector>

class FunctionDef: public Statement {
public:
  FunctionDef(ValType rettype, std::string name, std::vector<std::pair<ValType, std::string>> args): rettype_(rettype), name_(std::move(name)), args_(std::move(args)) {};

  void codegen(CompilerContext& nyacc_context) const override;

private:
  ValType rettype_;
  std::string name_;
  std::vector<std::pair<ValType, std::string>> args_;
};