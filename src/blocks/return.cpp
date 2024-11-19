#include <blocks/return.h>

void ReturnStatement::codegen(CompilerContext& context) const {
  auto retval = value_->codegen(context);
  context.builder.CreateRet(retval.val);
}