#include <blocks/program.h>

void Program::codegen(CompilerContext &nyacc_context) const {
  for (auto &function : content_) {
    function->codegen(nyacc_context);
  }
}