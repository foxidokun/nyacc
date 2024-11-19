#pragma once

#include <blocks/expression.h>
#include <blocks/statement.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <memory>

class ExprStatement: public Statement {
public:
  ExprStatement(std::unique_ptr<Expression> content): content_(std::move(content)) {};

  void codegen(CompilerContext& nyacc_context) const override;

private:
  std::unique_ptr<Expression> content_;
};