#include <blocks/expression.h>

class ValueExpression : public Expression {
public:
  ValueExpression(int val): val_(val) {}

  llvm::Value *codegen(llvm::LLVMContext& context, llvm::IRBuilder<>& builder) const override {return nullptr;};

private:
  int val_;
};