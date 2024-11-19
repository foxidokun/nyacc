#pragma once

#include <cstdint>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

// Forward decl
class CompilerContext;

struct ValType {
  enum class Kind: uint8_t {
    Int,
    UInt,
    Float
  };

  Kind kind;
  uint8_t bitwidth;

  bool operator==(const ValType&) const = default;

  // Helpful methods
  llvm::Type *llvm_type(llvm::LLVMContext&) const;
};

struct TypedValue {
  llvm::Value *val;
  ValType type;
};

TypedValue cast(CompilerContext& context, TypedValue val, ValType target_type);