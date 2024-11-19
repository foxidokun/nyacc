#include <blocks/expr_statement.h>

void ExprStatement::codegen(CompilerContext& context) const {
  content_->codegen(context);
}