%require "3.2"
%language "c++"

%code requires {
  #include <string>
  #include <blocks/common.h>
  #include <memory>

  class CustLexer;

  #include <blocks/let.h>
  #include <blocks/binop.h>
  #include <blocks/expression.h>
  #include <blocks/return.h>
  #include <blocks/statement.h>
  #include <blocks/value.h>
  #include <blocks/variable.h>
  #include <blocks/function.h>
  #include <blocks/program.h>
}

%define api.value.type variant
%define api.token.constructor

%parse-param {CustLexer &lexer}
%parse-param {std::unique_ptr<Program>& prog}

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
%nterm <std::unique_ptr<Function>> func_impl
%nterm <std::unique_ptr<std::vector<std::unique_ptr<Function>>>> functions
%nterm <std::unique_ptr<Program>> program

%left PLUS MINUS 
%left MUL DIV

%start program

%%

// Program is multiple function implementations
program: functions {
  prog = std::make_unique<Program>(std::move(*$1));
};

func_impl: type IDENTIFIER LBRACE RBRACE LCURVBRACE statements RCURVBRACE {
  $$ = std::make_unique<Function>(std::move($2), std::move(*$6));
};

statement: type IDENTIFIER ASSIGN expression SEMILICON {
  $$ = std::make_unique<LetStatement>(std::move($2), std::move($4));
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
statements: statement statements { $2->emplace_back(std::move($1)); $$ = std::move($2); } | statement {$$ = std::make_unique<std::vector<std::unique_ptr<Statement>>>(); $$->emplace_back(std::move($1)); } ;
functions: func_impl functions { $2->emplace_back(std::move($1)); $$ = std::move($2); } | func_impl {$$ = std::make_unique<std::vector<std::unique_ptr<Function>>>(); $$->emplace_back(std::move($1)); };
type: INTTYPE ;
value: INTEGER {
  $$ = std::make_unique<ValueExpression>($1);
} | IDENTIFIER {
  $$ = std::make_unique<VariableExpression>(std::move($1));
};

%%

void yy::parser::error(const std::string &message)
{
    std::cerr << "Error: " << message << std::endl;
}