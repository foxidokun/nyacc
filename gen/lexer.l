%{
    #include <FooLexer.h>
    #include <parser.gen.h>
    
    #undef  YY_DECL
    #define YY_DECL int FooLexer::yylex(std::string *const yylval)
%}

%option c++ noyywrap

%option yyclass="FooLexer"

%%

[[:space:]] ;
Hello { return yy::parser::token::HELLO; }
[[:alpha:]]+ { *yylval = std::string(yytext, yytext + yyleng); return yy::parser::token::WORLD; }
. { return yytext[0]; }
