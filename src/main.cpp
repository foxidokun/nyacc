#include <CustLexer.h>
#include <parser.gen.h>

int main()
{
  CustLexer lexer;
  yy::parser parser(lexer);
  return parser();
}
