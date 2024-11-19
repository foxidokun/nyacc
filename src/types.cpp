#include "context.h"
#include <cstdlib>
#include <fmt/base.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <types.h>

llvm::Type *ValType::llvm_type(llvm::LLVMContext& context) const {
  switch (kind) {
    case Kind::Int:
    case Kind::UInt:
      return llvm::Type::getIntNTy(context, bitwidth);
    case Kind::Float:
      switch (bitwidth) {
        case 32:
          return llvm::Type::getFloatTy(context);
        case 64:
          return llvm::Type::getDoubleTy(context);
      }
    case Kind::Void:
      return llvm::Type::getVoidTy(context);
  }

  fmt::println("Unexpected type");
  exit(1);
}

TypedValue cast(CompilerContext& context, TypedValue val, ValType target_type) {
  llvm::Value *cast_result;
  
  // Quickpath: nothing to do
  if (val.type == target_type) {
    return val;
  }

  // Sanity check
  if (target_type.kind == ValType::Kind::Void || val.type.kind == ValType::Kind::Void) {
    fmt::println(stderr, "Can't cast to/from void");
    exit(1);
  }

  int converted = 0;

  // int to int
  if (val.type.kind == ValType::Kind::Int && target_type.kind == ValType::Kind::Int) {
    cast_result = context.builder.CreateIntCast(val.val, target_type.llvm_type(context.llvm_context), true);
    ++converted;
  }

  // uint to (u)int
  if (val.type.kind == ValType::Kind::UInt && (target_type.kind == ValType::Kind::Int || target_type.kind == ValType::Kind::UInt)) {
    cast_result = context.builder.CreateIntCast(val.val, target_type.llvm_type(context.llvm_context), false);
    ++converted;
  }

  // int to float
  if (val.type.kind == ValType::Kind::Int && target_type.kind == ValType::Kind::Float) {
    cast_result = context.builder.CreateCast(llvm::Instruction::SIToFP, val.val, target_type.llvm_type(context.llvm_context));
    ++converted;
  }

  // uint to float
  if (val.type.kind == ValType::Kind::UInt && target_type.kind == ValType::Kind::Float) {
    cast_result = context.builder.CreateCast(llvm::Instruction::UIToFP, val.val, target_type.llvm_type(context.llvm_context));
    ++converted;
  }

  // float to float
  if (val.type.kind == ValType::Kind::Float && target_type.kind == ValType::Kind::Float) {
    cast_result = context.builder.CreateFPCast(val.val, target_type.llvm_type(context.llvm_context));
    ++converted;
  }

  // float to int (in assigments, etc)
  if (val.type.kind == ValType::Kind::Float && target_type.kind == ValType::Kind::Int) {
    cast_result = context.builder.CreateCast(llvm::Instruction::FPToSI, val.val, target_type.llvm_type(context.llvm_context));
    ++converted;
  }

  // float to uint (in assigments, etc)
  if (val.type.kind == ValType::Kind::Float && target_type.kind == ValType::Kind::UInt) {
    cast_result = context.builder.CreateCast(llvm::Instruction::FPToUI, val.val, target_type.llvm_type(context.llvm_context));
    ++converted;
  }

  assert (converted == 1);

  return TypedValue{cast_result, target_type};
}