#pragma once

#include <exception>
#include <stdexcept>
#include <types.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Value.h>
#include <string>
#include <unordered_map>
#include <vector>

class CompilerContext {
  using FuncType = std::pair<ValType, std::vector<ValType>>;

public:
  CompilerContext(llvm::LLVMContext& _llvm_context, llvm::IRBuilder<>& _builder, llvm::Module& _module):
  llvm_context(_llvm_context), builder(_builder), module(_module) {}

  void enter_visibility_block();
  void exit_visibility_block();

  TypedValue get_variable(const std::string& name) const;
  void insert_variable(const std::string& name, TypedValue val);

  // shared_ptr because no std::optional<T&> until c++26 :cry:
  std::shared_ptr<FuncType> get_function_type(const std::string& name) const;
  void set_function_type(const std::string& name, FuncType type);

  const std::string& current_function() const;
  void enter_function(std::string name);

// Storage for llvm
public:
llvm::LLVMContext& llvm_context;
llvm::IRBuilder<>& builder;
llvm::Module& module;

private:
  // Vector because of iterators
  std::vector<std::unordered_map<std::string, TypedValue>> variables_; 
  std::unordered_map<std::string, std::shared_ptr<FuncType>> functions_;
  std::string current_function_;
};

struct NyaccError: std::runtime_error {
  NyaccError(const char *text): std::runtime_error(text) {}
  NyaccError(std::string text): std::runtime_error(std::move(text)) {}
};