%require "3.2"
%language "c++"

%code requires {
    #include <string>
    #include <FooLexer.h>
}

%define api.value.type {std::string}

%parse-param {FooLexer &lexer}

%header

%code {
    #define yylex lexer.yylex
}

%token HELLO
%token WORLD

%%

hello_world: HELLO WORLD '!' { std::cout << "Goodbye " << $WORLD << '!' << std::endl; }

%%

void yy::parser::error(const std::string &message)
{
    std::cerr << "Error: " << message << std::endl;
}