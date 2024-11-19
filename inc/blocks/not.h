#include <blocks/expression.h>
#include <memory>

class NotExpression : public Expression {
public:
  NotExpression(std::unique_ptr<Expression> val): val_(std::move(val)) {}

  TypedValue codegen(CompilerContext& nyacc_context) const override;

private:
  std::unique_ptr<Expression> val_;
};