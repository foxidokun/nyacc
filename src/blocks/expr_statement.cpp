#include <blocks/expr_statement.h>

void ExprStatement::codegen(CompilerContext& context) const {
  if (content_) {
    content_->codegen(context);
  }
}