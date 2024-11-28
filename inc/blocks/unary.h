#include <blocks/expression.h>
#include <memory>

class UnaryExpression : public Expression {
public:
  enum class Op {
    Not,
    Minus
  };

  UnaryExpression(std::unique_ptr<Expression> val, Op oper): val_(std::move(val)), operator_(oper) {}

  TypedValue codegen(CompilerContext& nyacc_context) const override;

private:
  Op operator_;
  std::unique_ptr<Expression> val_;
};