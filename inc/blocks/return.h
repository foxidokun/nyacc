#pragma once

#include "blocks/expression.h"
#include <blocks/statement.h>
#include <memory>

class ReturnStatement: public Statement {
public:
  ReturnStatement(std::unique_ptr<Expression> value): value_(std::move(value)) {}
  virtual void codegen(CompilerContext& nyacc_context, llvm::LLVMContext& context, llvm::IRBuilder<>& builder) const override;

private:
  std::unique_ptr<Expression> value_;
};