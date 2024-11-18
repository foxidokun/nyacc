%require "3.2"
%language "c++"

%code requires {
  #include <string>
  class CustLexer;

  class SumExpression;
  class Expression;
}

%define api.value.type variant
%define api.token.constructor

%parse-param {CustLexer &lexer}

%code top {
    #include <CustLexer.h>
    #include <expressions/sum.h>
    #include <expressions/common.h>

    // #define yylex lexer.yylex

    #define yylex(...) lexer.get_next_token()
}

%token MINUS
%token PLUS
%token <std::string> IDENTIFIER
%token <int> INTEGER

%parse-param {Expression *& ast}

%nterm <SumExpression *> entrypoint

%start entrypoint 

%%

entrypoint: INTEGER op INTEGER {
  ast = new SumExpression($1, $3);
}

op: PLUS

%%

void yy::parser::error(const std::string &message)
{
    std::cerr << "Error: " << message << std::endl;
}