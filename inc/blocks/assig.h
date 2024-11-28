#pragma once

#include <blocks/expression.h>
#include <blocks/statement.h>
#include <context.h>
#include <memory>
#include <types.h>

class AssigStatement : public Statement {
public:
  AssigStatement(std::string name, std::unique_ptr<Expression> value)
      : name_(std::move(name)), value_(std::move(value)) {};
  virtual void codegen(CompilerContext &nyacc_context) const override;

private:
  std::string name_;
  std::unique_ptr<Expression> value_;
};