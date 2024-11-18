#pragma once

#include <llvm/IR/Value.h>
#include <string>
#include <unordered_map>
#include <vector>

class CompilerContext {
public:
  void enter_visibility_block();
  void exit_visibility_block();

  llvm::Value *get_variable(const std::string& name) const;
  void insert_variable(const std::string& name, llvm::Value * val);

private:
  // Vector because of iterators
  std::vector<std::unordered_map<std::string, llvm::Value *>> variables_; 
};