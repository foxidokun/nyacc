#include <blocks/common.h>
#include <blocks/expression.h>
#include <vector>

class FuncCallExpression : public Expression {
public:
  FuncCallExpression(std::string name,
                     std::vector<std::unique_ptr<Expression>> args)
      : name_(name), args_(std::move(args)) {}

  TypedValue codegen(CompilerContext &nyacc_context) const override;

private:
  std::string name_;
  std::vector<std::unique_ptr<Expression>> args_;
};