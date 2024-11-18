%{
    #include <CustLexer.h>
    #include <parser.gen.h>
    #include <climits>
%}

%option c++ noyywrap

%option yyclass="CustLexer"

id      [a-zA-Z][a-zA-Z_0-9]*
int     [0-9]+

%%

"-"       return yy::parser::make_MINUS();
"+"       return yy::parser::make_PLUS();
{int}     {
  errno = 0;
  long n = strtol(yytext, NULL, 10);
  if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE)) {
    throw yy::parser::syntax_error(std::string("integer is out of range: ") + yytext);
  }
  return yy::parser::make_INTEGER((int) n);
}

{id} return yy::parser::make_IDENTIFIER(std::string(yytext, yytext + yyleng));

. ;
