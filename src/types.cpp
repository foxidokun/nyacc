#include <cstdlib>
#include <fmt/base.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <types.h>

llvm::Type *ValType::llvm_type(llvm::LLVMContext& context) const {
  switch (kind) {
    case Kind::Int:
      return llvm::Type::getIntNTy(context, bitwidth);
    case Kind::Float:
      switch (bitwidth) {
        case 32:
          return llvm::Type::getFloatTy(context);
        case 64:
          return llvm::Type::getDoubleTy(context);
      }
  }

  fmt::println("Unexpected type");
  exit(1);
}