#pragma once

#include <types.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Value.h>
#include <string>
#include <unordered_map>
#include <vector>

class CompilerContext {
public:
  CompilerContext(llvm::LLVMContext& _llvm_context, llvm::IRBuilder<>& _builder, llvm::Module& _module):
  llvm_context(_llvm_context), builder(_builder), module(_module) {}

  void enter_visibility_block();
  void exit_visibility_block();

  TypedValue get_variable(const std::string& name) const;
  void insert_variable(const std::string& name, TypedValue val);

// Storage for llvm
public:
llvm::LLVMContext& llvm_context;
llvm::IRBuilder<>& builder;
llvm::Module& module;

private:
  // Vector because of iterators
  std::vector<std::unordered_map<std::string, TypedValue>> variables_; 
};