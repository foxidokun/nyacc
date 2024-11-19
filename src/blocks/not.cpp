#include "blocks/common.h"
#include "types.h"
#include <blocks/not.h>

TypedValue NotExpression::codegen(CompilerContext& context) const  {
  auto val = boolify(context, val_->codegen(context));
  auto res = context.builder.CreateNot(val.val);
  return {res, val.type};
}