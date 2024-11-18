%{
    #include <CustLexer.h>
    #include <parser.gen.h>
%}

%option c++ noyywrap

%option yyclass="CustLexer"

%%

[[:space:]] ;
Hello { return yy::parser::make_HELLO(); }
[[:alpha:]]+ { return yy::parser::make_WORLD("ABOBA"); }
. { return yytext[0]; }
