#include <blocks/expression.h>
#include <llvm/IR/GlobalVariable.h>

class StrExpression : public Expression {
public:
  StrExpression(std::string val) : val_(std::move(val)) {}

  TypedValue codegen(CompilerContext &nyacc_context) const override;

private:
  std::string val_;
};