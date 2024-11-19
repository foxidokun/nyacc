#pragma once

#include <blocks/expression.h>
#include <blocks/statement.h>
#include <context.h>
#include <memory>
#include <types.h>

class IfStatement : public Statement {
public:
  IfStatement(std::unique_ptr<Expression> condition,
              std::vector<std::unique_ptr<Statement>> if_content,
              std::vector<std::unique_ptr<Statement>> else_content)
      : condition_(std::move(condition)), if_content_(std::move(if_content)),
        else_content_(std::move(else_content)) {};

  virtual void codegen(CompilerContext &nyacc_context) const override;

private:
  std::unique_ptr<Expression> condition_;
  std::vector<std::unique_ptr<Statement>> if_content_;
  std::vector<std::unique_ptr<Statement>> else_content_;
};