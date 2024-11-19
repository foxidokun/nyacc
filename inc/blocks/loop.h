#pragma once

#include <blocks/expression.h>
#include <blocks/statement.h>
#include <context.h>
#include <memory>
#include <types.h>

class LoopStatement : public Statement {
public:
  LoopStatement(std::unique_ptr<Statement> start,
                std::unique_ptr<Statement> step,
                std::unique_ptr<Expression> condition,
                std::vector<std::unique_ptr<Statement>> content)
      : start_(std::move(start)), step_(std::move(step)),
        condition_(std::move(condition)), content_(std::move(content)) {};
  
  virtual void codegen(CompilerContext &nyacc_context) const override;

private:
  std::unique_ptr<Statement> start_;
  std::unique_ptr<Statement> step_;
  std::unique_ptr<Expression> condition_;
  std::vector<std::unique_ptr<Statement>> content_;
};