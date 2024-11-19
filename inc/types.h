#pragma once

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Type.h>

struct ValType {
  enum class Kind {
    Int,
    UInt,
    Float
  };

  Kind kind;
  int bitwidth;

  // Helpful methods
  llvm::Type *llvm_type(llvm::LLVMContext&) const;
};