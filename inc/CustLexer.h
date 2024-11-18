#pragma once

#include <parser.gen.h>
#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL yy::parser::symbol_type CustLexer::get_next_token()

class CustLexer: public yyFlexLexer {
public:
  CustLexer() = default;

  virtual yy::parser::symbol_type get_next_token();

  virtual ~CustLexer() = default;
};