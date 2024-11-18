#include <FooLexer.h>
#include <parser.gen.h>

int main()
{
  FooLexer lexer;
  yy::parser parser(lexer);
  return parser();
}
