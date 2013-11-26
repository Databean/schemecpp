#ifndef SCANNER_H
#define SCANNER_H

int yylex();

void yyerror(char* s);

void chooseStr ( const char *str );

void cleanBufferState();

#endif