#include <CustLexer.h>
#include <fcntl.h>
#include <fmt/base.h>
#include <fstream>
#include <llvm/Support/raw_ostream.h>
#include <memory>
#include <parser.gen.h>
#include <llvm/IR/Module.h>

#include <blocks/expression.h>
#include <sstream>
#include <system_error>

std::unique_ptr<Program> get_ast(const char *filename) {
  std::fstream input_file(filename);
  std::stringstream parser_out;

  CustLexer lexer;
  lexer.switch_streams(&input_file, &parser_out);

  std::unique_ptr<Program> prog;
  yy::parser parser(lexer, prog);
  parser();

  if (prog == nullptr) {
    fmt::println(stderr, "Failed to parse");
    exit(1);
  }

  return prog;
}

int main(int argc, char **argv) {
  if (argc != 3) {
    return 1;
  }

  std::unique_ptr<Program> prog = get_ast(argv[1]);

  auto LLVMContext = llvm::LLVMContext();
  auto LLVMModule = llvm::Module("jit", LLVMContext);

  // Create a new builder for the module.
  auto LLVMBuilder = llvm::IRBuilder<>(LLVMContext);

  // auto *FT =
  //     llvm::FunctionType::get(llvm::Type::getInt64Ty(LLVMContext), std::vector<llvm::Type *>(), false);

  // auto *F =
  //     llvm::Function::Create(FT, llvm::Function::ExternalLinkage, "main", LLVMModule);
  // auto block = ast->codegen(LLVMContext, LLVMBuilder);
  // auto *BB = llvm::BasicBlock::Create(LLVMContext, "entry", F);
  // LLVMBuilder.SetInsertPoint(BB);
  // LLVMBuilder.CreateRet(block);

  std::error_code ec;
  llvm::raw_fd_ostream out_file(argv[2], ec);

  LLVMModule.print(out_file, nullptr);
}
