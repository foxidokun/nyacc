#include <context.h>
#include <CustLexer.h>
#include <fcntl.h>
#include <fmt/base.h>
#include <fmt/printf.h>
#include <fstream>
#include <llvm/Support/raw_ostream.h>
#include <parser.gen.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/PassManager.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Analysis/LoopAnalysisManager.h>
#include <llvm/Analysis/CGSCCPassManager.h>

#include <blocks/program.h>
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
    throw NyaccError("Failed to parse AST");
  }

  return prog;
}

void run_optimizer(llvm::Module& module) {
  llvm::LoopAnalysisManager LAM;
  llvm::FunctionAnalysisManager FAM;
  llvm::CGSCCAnalysisManager CGAM;
  llvm::ModuleAnalysisManager MAM;

  llvm::PassBuilder PB;
  PB.registerModuleAnalyses(MAM);
  PB.registerCGSCCAnalyses(CGAM);
  PB.registerFunctionAnalyses(FAM);
  PB.registerLoopAnalyses(LAM);
  PB.crossRegisterProxies(LAM, FAM, CGAM, MAM);

  llvm::ModulePassManager MPM = PB.buildPerModuleDefaultPipeline(llvm::OptimizationLevel::O2);
  MPM.run(module,MAM);
}

int main(int argc, char **argv) 
try
{
  if (argc != 3) {
    return 1;
  }

  std::unique_ptr<Program> prog = get_ast(argv[1]);

  auto LLVMContext = llvm::LLVMContext();
  auto LLVMModule = llvm::Module("nyacc", LLVMContext);
  auto LLVMBuilder = llvm::IRBuilder<>(LLVMContext);

  CompilerContext nyacc_context(LLVMContext, LLVMBuilder, LLVMModule);

  // compile
  prog->codegen(nyacc_context);

  // optimize
  run_optimizer(LLVMModule);

  std::error_code ec;
  llvm::raw_fd_ostream out_file(argv[2], ec);

  LLVMModule.print(out_file, nullptr);
} catch (NyaccError& err) {
  fmt::println(stderr, "Compilation failed with err {}", err.what());
  return -1;
}
