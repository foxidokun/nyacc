#include <blocks/expression.h>
#include <variant>

class ValueExpression : public Expression {
public:
  ValueExpression(int64_t val): val_(val), kind_(ValType::Kind::Int) {}
  ValueExpression(double val): val_(val), kind_(ValType::Kind::Float) {}

  TypedValue codegen(CompilerContext& nyacc_context) const override;

private:
  std::variant<int64_t, double> val_;

  ValType::Kind kind_;
};