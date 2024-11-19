#include "types.h"
#include <blocks/return.h>

void ReturnStatement::codegen(CompilerContext& context) const {
  auto func_type = context.get_function_type(context.current_function());
  if (value_) {
    auto retval = value_->codegen(context);
    retval = cast(context, retval, func_type->first);
    context.builder.CreateRet(retval.val);
  } else {
    /* Return void */
    context.builder.CreateRet(nullptr);
  }
}