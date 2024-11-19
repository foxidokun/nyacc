#include <blocks/expression.h>

class VariableExpression : public Expression {
public:
  VariableExpression(std::string name): name_(std::move(name)) {}

  llvm::Value *codegen(CompilerContext& nyacc_context) const override;

private:
  std::string name_;
};