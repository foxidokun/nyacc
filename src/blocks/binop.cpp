#include "context.h"
#include "types.h"
#include <blocks/binop.h>
#include <cassert>
#include <fmt/base.h>
#include <fmt/format.h>
#include <llvm/ADT/APInt.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Value.h>

static ValType get_result_type(ValType lhs, ValType rhs);

#define DISPATCH_BINOP(op, float_func, int_func, uint_funt, restype) \
case OpSign::op:  \
  if (result_type.kind == ValType::Kind::Float) { \
    return {context.builder.float_func(lhs.val, rhs.val), restype}; \
  } else if (result_type.kind == ValType::Kind::Int) {  \
    return {context.builder.int_func(lhs.val, rhs.val), restype}; \
  } else { /*Uint*/  \
    return {context.builder.uint_funt(lhs.val, rhs.val), restype};  \
  }

TypedValue BinopExpression::codegen(CompilerContext& context) const {
  auto lhs = lhs_->codegen(context);
  auto rhs = rhs_->codegen(context);

  auto result_type = get_result_type(lhs.type, rhs.type);

  // Create casts

  lhs = cast(context, lhs, result_type);
  rhs = cast(context, rhs, result_type);

  // Create operations

  auto cmp_result_type = ValType{ValType::Kind::Int, 1};

  switch (type_) {
    DISPATCH_BINOP(Minus, CreateFSub, CreateSub, CreateSub, result_type)
    DISPATCH_BINOP(Plus, CreateFAdd, CreateAdd, CreateAdd, result_type)
    DISPATCH_BINOP(Mul, CreateFMul, CreateMul, CreateMul, result_type)
    DISPATCH_BINOP(Div, CreateFDiv, CreateSDiv, CreateUDiv, result_type)
    DISPATCH_BINOP(LT, CreateFCmpOLT, CreateICmpSLT, CreateICmpULT, cmp_result_type)
    DISPATCH_BINOP(LE, CreateFCmpOLE, CreateICmpSLE, CreateICmpULE, cmp_result_type)
    DISPATCH_BINOP(GT, CreateFCmpOGT, CreateICmpSGT, CreateICmpUGT, cmp_result_type)
    DISPATCH_BINOP(GE, CreateFCmpOGE, CreateICmpSGE, CreateICmpUGE, cmp_result_type)
    DISPATCH_BINOP(EQ, CreateFCmpOEQ, CreateICmpEQ, CreateICmpEQ, cmp_result_type)
    DISPATCH_BINOP(NE, CreateFCmpONE, CreateICmpNE, CreateICmpNE, cmp_result_type)
    default: 
    fmt::println(stderr, "Unexpected binop");
    exit(1);
  }
}

static ValType get_result_type(ValType lhs, ValType rhs) {
  if (lhs.kind == ValType::Kind::Void || lhs.kind == ValType::Kind::String || rhs.kind == ValType::Kind::Void || rhs.kind == ValType::Kind::String) {
    fmt::println(stderr, "Unsupported binop on void / string objects");
    exit(1);
  }

  // Both float 
  if (lhs.kind == ValType::Kind::Float && rhs.kind == ValType::Kind::Float) {
    return {ValType::Kind::Float, std::max(lhs.bitwidth, rhs.bitwidth)};
  }

  // Only one float
  if (lhs.kind == ValType::Kind::Float) { return lhs; }
  if (rhs.kind == ValType::Kind::Float) { return rhs; }

  // Both Uint => Keep UInt
  if (lhs.kind == ValType::Kind::UInt && rhs.kind == ValType::Kind::UInt) {
    return {ValType::Kind::UInt, std::max(lhs.bitwidth, rhs.bitwidth)};
  }

  // No floats, has int => int
  return {ValType::Kind::Int, std::max(lhs.bitwidth, rhs.bitwidth)};
}