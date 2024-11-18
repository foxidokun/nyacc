#include <CustLexer.h>
#include <fmt/base.h>
#include <parser.gen.h>
#include <fstream>

#include <expressions/common.h>
#include <sstream>

int main(int argc, char** argv) {
  if (argc != 2) {
    return 1;
  }

  std::fstream input_file(argv[1]);
  std::stringstream parser_out;

  CustLexer lexer;
  lexer.switch_streams(&input_file, &parser_out);

  Expression *ast = nullptr;
  yy::parser parser(lexer, ast);
  parser();

  if (ast ==nullptr) {
    fmt::println("Failed to parse");
    return 1;
  }

  fmt::println("PARSED {}", ast->format());
}
