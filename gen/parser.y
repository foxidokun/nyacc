%require "3.2"
%language "c++"

%code requires {
  #include <string>
  #include <blocks/common.h>
  #include <memory>

  class CustLexer;

  #include <blocks/assign.h>
  #include <blocks/binop.h>
  #include <blocks/expression.h>
  #include <blocks/return.h>
  #include <blocks/statement.h>
  #include <blocks/value.h>
}

%define api.value.type variant
%define api.token.constructor

%parse-param {CustLexer &lexer}

%code top {
    #include <CustLexer.h>

    #define yylex(...) lexer.get_next_token()
}

%token LBRACE RBRACE LCURVBRACE RCURVBRACE SEMILICON INTTYPE COMMA ASSIGN RETURN
%token <std::string> IDENTIFIER
%token <int> INTEGER

%nterm <std::unique_ptr<Statement>> statement
%nterm <std::unique_ptr<std::vector<std::unique_ptr<Statement>>>> statements
%nterm <std::unique_ptr<Expression>> expression
%nterm <std::unique_ptr<Expression>> value

%left PLUS MINUS 
%left MUL DIV

%start program

%%

// Program is multiple function implementations
program: func_impl program | %empty;

func_impl: type IDENTIFIER LBRACE RBRACE LCURVBRACE statements RCURVBRACE;

statement: type IDENTIFIER ASSIGN expression SEMILICON {
  $$ = std::make_unique<AssignStatement>($2, std::move($4));
} |
RETURN expression SEMILICON {
  $$ = std::make_unique<ReturnStatement>(std::move($2));
};

expression: value {$$ = std::move($1);} |
expression PLUS expression {
  $$ = std::make_unique<BinopExpression>(std::move($1), std::move($3), OpSign::Plus);
} |
expression MINUS expression {
  $$ = std::make_unique<BinopExpression>(std::move($1), std::move($3), OpSign::Minus);
} |
expression DIV expression {
  $$ = std::make_unique<BinopExpression>(std::move($1), std::move($3), OpSign::Div);
} |
expression MUL expression {
  $$ = std::make_unique<BinopExpression>(std::move($1), std::move($3), OpSign::Mul);
} |
LBRACE expression RBRACE {
  $$ = std::move($2);
}
;

// Вспомогательное
statements: statement statements { $2->emplace_back(std::move($1)); $$ = std::move($2); } | statement {$$ = std::make_unique<std::vector<std::unique_ptr<Statement>>>();} ;
type: INTTYPE ;
value: INTEGER {
  $$ = std::make_unique<ValueExpression>($1);
};

%%

void yy::parser::error(const std::string &message)
{
    std::cerr << "Error: " << message << std::endl;
}