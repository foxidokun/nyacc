%{
    #include <CustLexer.h>
    #include <parser.gen.h>
    #include <climits>
%}

%option c++ noyywrap

%option yyclass="CustLexer"

id      [a-zA-Z][a-zA-Z_0-9]*
int     [0-9]+
float   [0-9]+\.[0-9]+

%%

"-"       return yy::parser::make_MINUS();
"+"       return yy::parser::make_PLUS();
"*"       return yy::parser::make_MUL();
"/"       return yy::parser::make_DIV();

"("       return yy::parser::make_LBRACE();
")"       return yy::parser::make_RBRACE();

"{"       return yy::parser::make_LCURVBRACE();
"}"       return yy::parser::make_RCURVBRACE();

";"       return yy::parser::make_SEMILICON();
","       return yy::parser::make_COMMA();

"i8"      return yy::parser::make_TYPE(ValType(ValType::Kind::Int, 8));
"i16"     return yy::parser::make_TYPE(ValType(ValType::Kind::Int, 16));
"i32"     return yy::parser::make_TYPE(ValType(ValType::Kind::Int, 32));
"i64"     return yy::parser::make_TYPE(ValType(ValType::Kind::Int, 64));

"u8"      return yy::parser::make_TYPE(ValType(ValType::Kind::UInt, 8));
"u16"     return yy::parser::make_TYPE(ValType(ValType::Kind::UInt, 16));
"u32"     return yy::parser::make_TYPE(ValType(ValType::Kind::UInt, 32));
"u64"     return yy::parser::make_TYPE(ValType(ValType::Kind::UInt, 64));

"f32"     return yy::parser::make_TYPE(ValType(ValType::Kind::Float, 32));
"f64"     return yy::parser::make_TYPE(ValType(ValType::Kind::Float, 64));

"void"    return yy::parser::make_TYPE(ValType(ValType::Kind::Void, 0));

"return"  return yy::parser::make_RETURN();

"="       return yy::parser::make_ASSIGN();

{int}     {
  errno = 0;
  long n = strtoll(yytext, NULL, 10);
  if (errno == ERANGE) {
    throw yy::parser::syntax_error(std::string("integer is out of range: ") + yytext);
  }
  return yy::parser::make_INTEGER(n);
}

{float} {
  errno = 0;
  double n = strtod(yytext, NULL);
  if (errno == ERANGE) {
    throw yy::parser::syntax_error(std::string("double is out of range: ") + yytext);
  }
  return yy::parser::make_DOUBLE(n);
}

{id} return yy::parser::make_IDENTIFIER(std::string(yytext, yytext + yyleng));

. ;
