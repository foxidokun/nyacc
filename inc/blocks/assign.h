#pragma once

#include "blocks/expression.h"
#include <blocks/statement.h>
#include <memory>

class AssignStatement: public Statement {
public:
  AssignStatement(std::string name, std::unique_ptr<Expression> value): name_(std::move(name)), value_(std::move(value)) {};
  virtual void codegen(llvm::LLVMContext& context, llvm::IRBuilder<>& builder) const override {}

private:
  std::string name_;
  std::unique_ptr<Expression> value_;
};