#pragma once

#include <blocks/expression.h>
#include <blocks/statement.h>
#include <context.h>
#include <memory>
#include <types.h>

class LetStatement : public Statement {
public:
  LetStatement(ValType type, std::string name,
               std::unique_ptr<Expression> value)
      : type_(type), name_(std::move(name)), value_(std::move(value)) {};
  virtual void codegen(CompilerContext &nyacc_context) const override;

private:
  ValType type_;
  std::string name_;
  std::unique_ptr<Expression> value_;
};