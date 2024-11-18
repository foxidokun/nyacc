#include <context.h>
#include <unordered_map>

void CompilerContext::enter_visibility_block() {
  variables_.push_back(std::unordered_map<std::string, llvm::Value *>());
}

void CompilerContext::exit_visibility_block() {
  variables_.pop_back();
}

llvm::Value *CompilerContext::get_variable(const std::string& name) const {
  // Searching from local to global
  for (auto layer_it = variables_.rbegin(), layer_end = variables_.rend(); layer_it < layer_end; ++layer_it) {
    auto &layer = *layer_it;
    auto val = layer.find(name);
    if (val != layer.end()) {
      return val->second;
    }
  }

  return nullptr;
}

void CompilerContext::insert_variable(const std::string& name, llvm::Value * val) {
  variables_.back()[name] = val;
}