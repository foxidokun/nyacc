#include <context.h>
#include <optional>
#include <types.h>
#include <unordered_map>

void CompilerContext::enter_visibility_block() {
  variables_.push_back(std::unordered_map<std::string, TypedValue>());
}

void CompilerContext::exit_visibility_block() { variables_.pop_back(); }

TypedValue CompilerContext::get_variable(const std::string &name) const {
  // Searching from local to global
  for (auto layer_it = variables_.rbegin(), layer_end = variables_.rend();
       layer_it < layer_end; ++layer_it) {
    auto &layer = *layer_it;
    auto val = layer.find(name);
    if (val != layer.end()) {
      return val->second;
    }
  }

  return TypedValue{.val = nullptr};
}

void CompilerContext::insert_variable(const std::string &name, TypedValue val) {
  variables_.back()[name] = val;
}

auto CompilerContext::get_function_type(const std::string &name) const
    -> std::shared_ptr<FuncType> {
  auto res_it = functions_.find(name);
  if (res_it == functions_.end()) {
    return nullptr;
  }

  return res_it->second;
}

void CompilerContext::set_function_type(const std::string &name,
                                        FuncType type) {
  functions_[name] = std::make_shared<FuncType>(std::move(type));
}

const std::string &CompilerContext::current_function() const {
  return current_function_;
}

void CompilerContext::enter_function(std::string name) {
  current_function_ = std::move(name);
}