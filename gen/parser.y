%require "3.2"
%language "c++"

%code requires {
    #include <string>
    class CustLexer;
}

%define api.value.type variant
%define api.token.constructor

%parse-param {CustLexer &lexer}

%code top {
    #include <CustLexer.h>

    // #define yylex lexer.yylex

    #define yylex(...) lexer.get_next_token()
}

%token HELLO
%token <std::string> WORLD

%%

hello_world: HELLO WORLD '!' { std::cout << "Goodbye " << $WORLD << '!' << std::endl; }

%%

void yy::parser::error(const std::string &message)
{
    std::cerr << "Error: " << message << std::endl;
}