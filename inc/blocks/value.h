#include <blocks/expression.h>

class ValueExpression : public Expression {
public:
  ValueExpression(int val): val_(val) {}

  llvm::Value *codegen(CompilerContext& nyacc_context) const override;

private:
  int val_;
};