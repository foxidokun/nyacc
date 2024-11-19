%require "3.2"
%language "c++"

%code requires {
  #include <string>
  #include <blocks/common.h>
  #include <memory>

  class CustLexer;

  #include <blocks/let.h>
  #include <blocks/assig.h>
  #include <blocks/binop.h>
  #include <blocks/expression.h>
  #include <blocks/return.h>
  #include <blocks/statement.h>
  #include <blocks/value.h>
  #include <blocks/variable.h>
  #include <blocks/function.h>
  #include <blocks/function_def.h>
  #include <blocks/program.h>
  #include <types.h>
}

%define api.value.type variant
%define api.token.constructor

%parse-param {CustLexer &lexer}
%parse-param {std::unique_ptr<Program>& prog}

%code top {
    #include <CustLexer.h>

    #define yylex(...) lexer.get_next_token()
}

%token LBRACE RBRACE LCURVBRACE RCURVBRACE SEMILICON COMMA ASSIGN RETURN
%token <std::string> IDENTIFIER
%token <int64_t> INTEGER
%token <double> DOUBLE
%token <ValType> TYPE

// unique_ptr on vector just to be sure that copying is avoided

%nterm <std::unique_ptr<Statement>> statement
%nterm <std::unique_ptr<std::vector<std::unique_ptr<Statement>>>> statements
%nterm <std::unique_ptr<Expression>> expression
%nterm <std::unique_ptr<Expression>> value
%nterm <std::unique_ptr<Statement>> func_impl
%nterm <std::unique_ptr<Statement>> func_def
%nterm <std::unique_ptr<std::vector<std::unique_ptr<Statement>>>> functions
%nterm <std::unique_ptr<Program>> program
%nterm <std::unique_ptr<std::vector<std::pair<ValType, std::string>>>> args

%left PLUS MINUS 
%left MUL DIV

%start program

%%

// Program is multiple function implementations
program: functions {
  // Because they are added in reverse order
  std::reverse($1->begin(), $1->end());
  prog = std::make_unique<Program>(std::move(*$1));
};

func_impl: TYPE IDENTIFIER LBRACE args RBRACE LCURVBRACE statements RCURVBRACE {
  // Because they are added in reverse order
  std::reverse($7->begin(), $7->end());
  std::reverse($4->begin(), $4->end());
  $$ = std::make_unique<Function>($1, std::move($2), std::move(*$4), std::move(*$7));
};

func_def: TYPE IDENTIFIER LBRACE args RBRACE SEMILICON {
  std::reverse($4->begin(), $4->end());
  $$ = std::make_unique<FunctionDef>($1, std::move($2), std::move(*$4));
};

statement: TYPE IDENTIFIER ASSIGN expression SEMILICON {
  $$ = std::make_unique<LetStatement>($1, std::move($2), std::move($4));
} |
RETURN expression SEMILICON {
  $$ = std::make_unique<ReturnStatement>(std::move($2));
} |
IDENTIFIER ASSIGN expression SEMILICON {
  $$ = std::make_unique<AssigStatement>(std::move($1), std::move($3));
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

value: INTEGER {
  $$ = std::make_unique<ValueExpression>($1);
} | DOUBLE {
  $$ = std::make_unique<ValueExpression>($1);
} | IDENTIFIER {
  $$ = std::make_unique<VariableExpression>(std::move($1));
};

// Списки
statements: statement statements { $2->emplace_back(std::move($1)); $$ = std::move($2); } | statement {$$ = std::make_unique<std::vector<std::unique_ptr<Statement>>>(); $$->emplace_back(std::move($1)); } ;
functions:
  func_impl functions { $2->emplace_back(std::move($1)); $$ = std::move($2); } |
  func_def functions { $2->emplace_back(std::move($1)); $$ = std::move($2); } |
  %empty {$$ = std::make_unique<std::vector<std::unique_ptr<Statement>>>();};
args: TYPE IDENTIFIER {
  $$ = std::make_unique<std::vector<std::pair<ValType, std::string>>>();
  $$->emplace_back($1, std::move($2));
} |
TYPE IDENTIFIER COMMA args {
  $4->emplace_back($1, std::move($2));
  $$ = std::move($4);
}
| %empty { $$ = std::make_unique<std::vector<std::pair<ValType, std::string>>>(); };

%%

void yy::parser::error(const std::string &message)
{
    std::cerr << "Error: " << message << std::endl;
}