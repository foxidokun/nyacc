#include <CustLexer.h>
#include <fcntl.h>
#include <fmt/base.h>
#include <fstream>
#include <llvm/Support/raw_ostream.h>
#include <parser.gen.h>
#include <llvm/IR/Module.h>

#include <expressions/common.h>
#include <sstream>
#include <system_error>

Expression *get_ast(const char *filename) {
  std::fstream input_file(filename);
  std::stringstream parser_out;

  CustLexer lexer;
  lexer.switch_streams(&input_file, &parser_out);

  Expression *ast = nullptr;
  yy::parser parser(lexer, ast);
  parser();

  if (ast == nullptr) {
    fmt::println("Failed to parse");
    exit(1);
  }

  fmt::println("PARSED {}", ast->format());

  return ast;
}

int main(int argc, char **argv) {
  if (argc != 3) {
    return 1;
  }

  Expression *ast = get_ast(argv[1]);

  auto LLVMContext = llvm::LLVMContext();
  auto LLVMModule = llvm::Module("jit", LLVMContext);

  // Create a new builder for the module.
  auto LLVMBuilder = llvm::IRBuilder<>(LLVMContext);

  auto *FT =
      llvm::FunctionType::get(llvm::Type::getInt64Ty(LLVMContext), std::vector<llvm::Type *>(), false);

  auto *F =
      llvm::Function::Create(FT, llvm::Function::ExternalLinkage, "main", LLVMModule);
  auto block = ast->codegen(LLVMContext, LLVMBuilder);
  auto *BB = llvm::BasicBlock::Create(LLVMContext, "entry", F);
  LLVMBuilder.SetInsertPoint(BB);
  LLVMBuilder.CreateRet(block);

  std::error_code ec;
  llvm::raw_fd_ostream out_file(argv[2], ec);

  LLVMModule.print(out_file, nullptr);
}
