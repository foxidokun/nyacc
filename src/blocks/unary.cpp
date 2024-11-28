#include "blocks/common.h"
#include "types.h"
#include <blocks/unary.h>
#include <cstdlib>
#include <fmt/base.h>

TypedValue UnaryExpression::codegen(CompilerContext& context) const  {
  if (operator_ == Op::Not) {
    auto val = boolify(context, val_->codegen(context));
    auto res = context.builder.CreateNot(val.val);
    return {res, val.type};
  }

  if (operator_ == Op::Minus) {
    auto val = val_->codegen(context);
    if (val.type.kind == ValType::Kind::Float) {
      auto neg = context.builder.CreateFNeg(val.val);
      return {neg, val.type};
    } else if (val.type.kind == ValType::Kind::Int || val.type.kind == ValType::Kind::UInt) {
      auto neg = context.builder.CreateNeg(val.val);
      return {neg, val.type};
    } else {
      fmt::println(stderr, "Unsupported unary minus on void / string objects");
      exit(1);
    }
  }

  // Unreachable
  exit(1);
}