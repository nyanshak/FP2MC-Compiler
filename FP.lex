%{
/*****************************************************************
This is a sample program for using lex to extract tokens and then
invoke a parser function and pass the token as a parameter to parse.
You will need to implement the parsing function (not using yacc)
to achieve parsing and parse tree building.
*****************************************************************/

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <cstdlib>

#include "y.tab.h"
using namespace std;

int lineNum = 1;

#define YYSTYPE int
extern YYSTYPE yyltype;

void error_input ();

void removeChar(char *str, char garbage) {

    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != garbage) dst++;
    }
    *dst = '\0';
}

#define yyterminate() return END

%}

%s LSTATE

OP		"-"
PositiveInteger 0|[1-9][0-9]*
Integer	(-?[ ]*{PositiveInteger})
Real {Integer}"."[0-9]+
ID [a-z]+
LPAREN	\(
RPAREN	\)
SLASH	\\
CHARACTER_STRING        ({LPAREN}([ a-zA-Z0-9]|({SLASH}n))+{RPAREN})

%%

{CHARACTER_STRING}	{	BEGIN 0; 
				yylval.lineNum = lineNum;
				char *res = (char*) malloc(strlen(yytext) + 1);
				strcpy(res, yytext);
				
				yylval.char_string = res;
				return Character_String;
			}



"CONSTANTS"	{ BEGIN 0; yylval.lineNum = lineNum; return CONSTANTS; }
"FUNCTIONS"	{ BEGIN 0; yylval.lineNum = lineNum; return FUNCTIONS; }
"MAIN"		{ BEGIN 0; yylval.lineNum = lineNum; return MAIN; }
<LSTATE>"{-"		{ BEGIN 0; yylval.char_string = "-"; return Function; }
<INITIAL>"{-"		{ BEGIN LSTATE;
				yylval.lineNum = lineNum;
				unput('-'); unput('{');
				return Lbracket; }
"{"		{ BEGIN 0; yylval.lineNum = lineNum; return Lbracket; }
"}"		{ BEGIN 0; yylval.lineNum = lineNum; return Rbracket; }
loop		{ BEGIN 0; yylval.lineNum = lineNum; return Loop; }
print		{ BEGIN 0; yylval.lineNum = lineNum; return Print; }

read		{ BEGIN 0; yylval.lineNum = lineNum; return Read; }
return		{ BEGIN 0; yylval.lineNum = lineNum; return Return; }
if		{ BEGIN 0; yylval.lineNum = lineNum; return If; }
then		{ BEGIN 0; yylval.lineNum = lineNum; return Then; }
else		{ BEGIN 0; yylval.lineNum = lineNum; return Else; }
while		{ BEGIN 0; yylval.lineNum = lineNum; return While; }

"=="		{ BEGIN 0; yylval.lineNum = lineNum; return EQ; }
">="		{ BEGIN 0; yylval.lineNum = lineNum; return GTE; }
"<="		{ BEGIN 0; yylval.lineNum = lineNum; return LTE; }
">"		{ BEGIN 0; yylval.lineNum = lineNum; return GT; }
"<"		{ BEGIN 0; yylval.lineNum = lineNum; return LT; }
"!="		{ BEGIN 0; yylval.lineNum = lineNum; return NEQ; }

=		{ BEGIN 0; yylval.lineNum = lineNum; return Assign; }
"**"		{ BEGIN 0; yylval.char_string = yytext; return Function; }
"+"|"*"|"-"|"/"	{ BEGIN 0; yylval.char_string = yytext; return Function; }
"T"		{ BEGIN 0; yylval.bval = true; return Boolean; }
"F"		{ BEGIN 0; yylval.bval = false; return Boolean; }
{Real}		{
			BEGIN 0;
			removeChar(yytext, ' ');
			yylval.num = atof(yytext);
			return Real;
		}

{Integer}	{
			BEGIN 0;
			removeChar(yytext, ' ');
			yylval.num = atof(yytext);
			return Integer;
		}

{ID}		{
			BEGIN 0; 	
			char* res = (char*) malloc(strlen(yytext) + 1);
			strcpy(res, yytext);
			yylval.char_string = res;
			return Identifier;
		}
[ \t]*		{}
\n		{ lineNum++; }
.		{ error_input(); }

%%

/*
int yywrap () {
	yytext = "$";
	cout << "EOF";
	return EndIn;
}*/



void error_input () {
	printf ("illegitimate token: %s on line %d\n", yytext, lineNum);
	exit (-1);
}

