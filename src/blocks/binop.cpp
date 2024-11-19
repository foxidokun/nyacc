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

TypedValue BinopExpression::codegen(CompilerContext& context) const {
  auto lhs = lhs_->codegen(context);
  auto rhs = rhs_->codegen(context);

  auto result_type = get_result_type(lhs.type, rhs.type);

  // Create casts

  lhs = cast(context, lhs, result_type);
  rhs = cast(context, rhs, result_type);

  // Create operations

  switch (type_) {
    case OpSign::Minus: 
      if (result_type.kind == ValType::Kind::Float) {
        return {context.builder.CreateFSub(lhs.val, rhs.val), result_type};
      } else {
        return {context.builder.CreateSub(lhs.val, rhs.val), result_type};
      }
    case OpSign::Plus:
      if (result_type.kind == ValType::Kind::Float) {
        return {context.builder.CreateFAdd(lhs.val, rhs.val), result_type};
      } else {
        return {context.builder.CreateAdd(lhs.val, rhs.val), result_type};
      }
    case OpSign::Mul: 
      if (result_type.kind == ValType::Kind::Float) {
        return {context.builder.CreateFMul(lhs.val, rhs.val), result_type};
      } else {
        return {context.builder.CreateMul(lhs.val, rhs.val), result_type};
      }
    case OpSign::Div: 
      if (result_type.kind == ValType::Kind::Float) {
        return {context.builder.CreateFDiv(lhs.val, rhs.val), result_type};
      } else if (result_type.kind == ValType::Kind::Int) {
        return {context.builder.CreateSDiv(lhs.val, rhs.val), result_type};
      } else { // UInt
        return {context.builder.CreateUDiv(lhs.val, rhs.val), result_type};
      }
    default:
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