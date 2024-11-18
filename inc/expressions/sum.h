#include <expressions/common.h>

class SumExpression : public Expression {
public:
  SumExpression(int lhs, int rhs) : lhs_(lhs), rhs_(rhs) {}

  std::string format() const override;
  llvm::Value *codegen(llvm::LLVMContext& context, llvm::IRBuilder<>& builder) const override;

private:
  int lhs_;
  int rhs_;
};