#include <blocks/expression.h>
#include <blocks/common.h>
#include <memory>

class BinopExpression : public Expression {
public:
  BinopExpression(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs, OpSign type) : lhs_(std::move(lhs)), rhs_(std::move(rhs)), type_(type) {}

  llvm::Value *codegen(llvm::LLVMContext& context, llvm::IRBuilder<>& builder) const override;

private:
  std::unique_ptr<Expression> lhs_;
  std::unique_ptr<Expression> rhs_;
  OpSign type_;
};