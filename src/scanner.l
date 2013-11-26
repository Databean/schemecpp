%{
#include "y.tab.h"
#include "scanner.h"
#include <string>
YY_BUFFER_STATE bufferState;
%}

%option noyywrap

WHITESPACE		[ \t\r\n]+
DIGIT		[0-9]
INTEGER		("-"?){DIGIT}+
LETTER		[a-zA-Z]|"!"|"$"|"%"|"&"|"*"|"+"|"-"|"."|"/"|":"|"<"|"="|">"|"?"|"@"|"^"|"_"|"~"
IDENTIFIER	{LETTER}({DIGIT}|{LETTER})*

%%

{WHITESPACE}	{ ; }
"#t"			{ yylval.boolExpr = true; return T_Bool; }
"#f"			{ yylval.boolExpr = false; return T_Bool; }
"-"?{INTEGER}	{ yylval.integer = atoi(yytext); return T_Integer; }
"."				{ return '.'; }
{IDENTIFIER}	{ yylval.str = new std::string(yytext); return T_Identifier; }
.				{ return *yytext; }

%%

void yyerror(char* s) {
	fprintf (stderr, "%s\n", s);
}

void chooseStr(const char* text) {
	bufferState = yy_scan_string(text);
}

void cleanBufferState() {
	yy_delete_buffer(bufferState);
}