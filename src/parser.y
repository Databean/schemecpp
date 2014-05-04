%{
#include "y.tab.h"
#include "Object.h"
#include "Number.h"


extern pscheme::Pair* root;

%}

%code requires {

#include <string>
#include "scanner.h"
#include "Object.h"
extern pscheme::Pair* root;

}

%union {
	std::string* str;
	int integer;
	bool boolExpr;
	pscheme::Pair* expressionList;
	pscheme::Object* expression;
}

%token <str> T_Identifier
%token <integer> T_Integer
%token <boolExpr> T_Bool

%type <expressionList> ExpressionList Root
%type <expression> Expression QuoteExpression

%%

Root				:	ExpressionList				{ root = $1; }
					;

ExpressionList		:	Expression ExpressionList	{ $$ = new pscheme::Pair($1,$2); }
					|	Expression '.' Expression	{ $$ = new pscheme::Pair($1,$3); }
					|	Expression					{ $$ = new pscheme::Pair($1,new pscheme::EmptyList()); }
					;

Expression			:	QuoteExpression				{ $$ = $1; }
					|	'(' ExpressionList ')'		{ $$ = $2; }
					|	'(' ')'						{ $$ = new pscheme::Pair(nullptr,new pscheme::EmptyList()); }
					|	T_Identifier				{ $$ = new pscheme::Identifier($1); }
					|	T_Integer					{ $$ = new pscheme::Number($1); }
					|	T_Bool						{ $$ = new pscheme::Bool($1); }
					;

QuoteExpression		:	'\'' QuoteExpression		{ $$ = new pscheme::Symbol($2); }
					|	'\'' T_Integer				{ $$ = new pscheme::Number($2); }
					|	'\'' T_Bool					{ $$ = new pscheme::Bool($2); }
					|	'\'' T_Identifier			{ $$ = new pscheme::Symbol(new pscheme::Identifier($2)); }
					|	'\'' '(' ExpressionList ')'	{ $$ = new pscheme::Symbol($3); }
					|	'\'' '(' ')'				{ $$ = new pscheme::EmptyList(); }
					;

%%