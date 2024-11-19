#pragma once

#include "context.h"
#include "types.h"

//TODO Rename to BinaryOp
enum class OpSign {
  Minus,
  Plus,
  Mul,
  Div,
  LT,
  GT,
  LE,
  GE,
  EQ,
  NE
};

TypedValue boolify(CompilerContext& context, TypedValue val);