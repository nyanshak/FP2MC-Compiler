#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#include <stdlib.h>
#include <string.h>

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20070509

#define YYEMPTY (-1)
#define yyclearin    (yychar = YYEMPTY)
#define yyerrok      (yyerrflag = 0)
#define YYRECOVERING (yyerrflag != 0)

extern int yyparse(void);

static int yygrowstack(void);
#define YYPREFIX "yy"
#line 2 "FP.yacc"
using namespace std;

#include <iostream>
#include <fstream>
#include <vector>
#include "defines.h"
int yylex(void);
void yyerror(char*);

int findSymbolIndex(string s);
void printInstructions();
void printSymbolTable();
void printSymbolTable();
void patch();

ofstream outfile;
int ln = 1, mcln = 1;

#define MAX_SYMBOLS 1000
#define NUMBER 1
#define BOOLEAN 2
#define CHAR_STRING 3
#define INTEGER 4
#define REAL 5
#define FUNC 6
#define IDENTIFIER 7
#define MAX_M_ADDR 100
Symbol sym_table[1000];
int num_syms = 0;
int m_addr = 0;
int fix = -1;

sparam sp;
vector<string> instructions;
vector<string> args;
int registers[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

void DEBUGLAST() {
	cout << "DEBUG: <" << instructions.back() << ">" << endl;
}

int findRegister() {
	int i = 0;
	for (; i < sizeof(registers) / sizeof(registers[0]); i++) {
		if (registers[i] == 1) {
			return i;
		}
	}
	yyerror("No registers available. Exiting");
	return -1;
}

void claimRegister(int s) {
	registers[s] = 0;
}

void freeRegister(int s) {
	registers[s] = 1;
}

string createGoto(int instr) {
	stringstream ss;
	ss << "goto " << instr << ";";
	return ss.str();
}
#line 69 "FP.yacc"
typedef union {
	float num;
	char* char_string;
	bool bval;
	int lineNum;
} YYSTYPE;
#line 96 "y.tab.c"
#define Character_String 257
#define Function 258
#define Identifier 259
#define Integer 260
#define Real 261
#define CONSTANTS 262
#define MAIN 263
#define FUNCTIONS 264
#define Return 265
#define Read 266
#define Print 267
#define If 268
#define Then 269
#define Else 270
#define While 271
#define EQ 272
#define NEQ 273
#define GTE 274
#define LTE 275
#define GT 276
#define LT 277
#define Loop 278
#define Assign 279
#define Lbracket 280
#define Rbracket 281
#define Boolean 282
#define END 0
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,   34,   36,   17,   37,   38,   35,   35,   39,    1,
    1,    1,    3,    3,   18,   18,   40,   28,   41,   41,
    2,    2,    8,    8,    8,    8,    8,    8,    9,   42,
   29,    4,    4,    4,   43,    5,    5,    5,    5,   27,
   23,   23,   24,   22,   22,   22,   21,   26,   20,   20,
   10,   30,   30,   11,   31,   31,   32,   32,   12,    7,
   15,   25,   14,   16,   13,   19,    6,    6,   33,   33,
   33,   33,   33,   33,
};
short yylen[] = {                                         2,
    7,    1,    1,    1,    1,    1,    0,    2,    4,    1,
    1,    1,    1,    1,    0,    2,    7,    1,    1,    2,
    0,    2,    1,    1,    1,    1,    1,    1,    5,    1,
    1,    1,    1,    1,    0,    3,    5,    6,    3,    1,
    1,    2,    5,    1,    1,    1,    2,    0,    3,    2,
    4,    1,    2,    4,    1,    2,    1,    1,    8,    1,
    1,    1,    4,    2,    4,    2,    5,    3,    1,    1,
    1,    1,    1,    1,
};
short yydefred[] = {                                      0,
    2,    0,    7,    0,    3,    5,   15,    0,    8,    0,
    0,    4,   21,    0,   18,   16,   12,   13,   14,   11,
    0,   10,    0,    0,    6,    9,    1,   22,   23,   24,
   25,   26,   28,   27,    0,    0,    0,    0,    0,    0,
    0,    0,   30,   21,   21,    0,   20,    0,   52,    0,
   57,   58,    0,   55,   60,    0,    0,   66,   64,    0,
    0,    0,   21,   53,   51,   56,   54,   61,   21,   69,
   70,   71,   72,   73,   74,    0,    0,   63,   65,   33,
   34,   31,   32,   48,    0,    0,    0,    0,    0,   68,
    0,    0,    0,   45,   46,   44,    0,    0,   29,   35,
   47,   17,   62,   21,    0,   36,    0,   42,   39,    0,
    0,   67,   49,    0,   59,    0,    0,   37,   38,
};
short yydgoto[] = {                                       2,
   52,   23,   81,   82,   83,   55,   56,   28,   29,   30,
   31,   32,   33,   34,   69,   44,   13,   10,   45,   92,
   84,   97,   98,   85,  104,   93,  117,   14,   86,   50,
   53,   54,   77,    3,    4,    7,   87,   26,    9,   16,
   37,   46,  110,
};
short yysindex[] = {                                   -236,
    0,    0,    0, -253,    0,    0,    0, -220,    0, -238,
 -237,    0,    0, -219,    0,    0,    0,    0,    0,    0,
 -222,    0,    1, -204,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, -152, -204, -201, -198, -247, -212,
 -212, -179,    0,    0,    0, -173,    0, -172,    0, -252,
    0,    0, -211,    0,    0, -177, -139,    0,    0, -263,
 -263, -170,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, -222, -170,    0,    0,    0,
    0,    0,    0,    0, -148, -222, -226, -263, -218,    0,
 -170, -222, -170,    0,    0,    0, -148, -222,    0,    0,
    0,    0,    0,    0, -222,    0,    0,    0,    0, -148,
 -263,    0,    0, -186,    0,    0, -222,    0,    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, -169,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, -188,    0,    0,    0,
    0,    0,    0,    0,    0,    0, -182,    0,    0,    0,
    0,    0,    0,    0,    0, -178,    0,    0,    0,
};
short yygindex[] = {                                      0,
   86,  -41,   -9,  -26,  -76,   59,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   -3,
    0,  -56,    9,    0,    0,    0,    0,    0,    0,    0,
    0,   55,    0,    0,    0,    0,   -4,  -45,    0,    0,
   73,    0,    0,
};
#define YYTABLESIZE 281
short yytable[] = {                                       8,
   27,   22,   60,   61,   65,   15,   64,   67,   96,   17,
    5,   51,   18,   19,   78,   79,    6,   25,   35,   17,
   96,   88,   18,   19,   12,    1,    6,   89,   25,   22,
   90,  100,  101,   96,   20,   57,   57,   96,   11,   24,
   99,    6,  102,   22,   20,   17,  106,   51,   18,   19,
   91,  103,  109,  114,   36,   35,   35,  116,   25,  112,
   49,    6,  111,   48,  105,  115,  107,    6,  118,   25,
   20,  119,   94,   18,   19,   95,   48,   48,   48,   59,
   43,   43,   43,   35,   35,   62,   63,   95,   80,   18,
   19,   68,   41,    6,   25,   19,   21,   48,   50,   58,
   95,   43,   40,  113,   95,  108,   35,   66,   47,    6,
   94,   18,   19,   38,   39,   40,    0,    0,   41,    0,
    0,    0,    0,    0,    0,   42,   43,    0,    0,    0,
    0,    6,   70,   71,   72,   73,   74,   75,    0,    0,
    0,    0,   76,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    6,
};
short yycheck[] = {                                       4,
    0,   11,   44,   45,   50,   10,  259,   53,   85,  257,
  264,  259,  260,  261,   60,   61,  280,  281,   23,  257,
   97,   63,  260,  261,  263,  262,  280,   69,  281,   39,
   76,  258,  259,  110,  282,   40,   41,  114,  259,  259,
   86,  280,   88,   53,  282,  257,   92,  259,  260,  261,
   77,  270,   98,  110,  259,   60,   61,  114,  281,  105,
  259,  280,  104,  265,   91,  111,   93,  280,  114,  281,
  282,  117,  259,  260,  261,   85,  259,  260,  261,  259,
  259,  260,  261,   88,   89,  259,  259,   97,  259,  260,
  261,  269,  281,  280,  281,  265,   11,  280,  281,   41,
  110,  280,  281,  107,  114,   97,  111,   53,   36,  280,
  259,  260,  261,  266,  267,  268,   -1,   -1,  271,   -1,
   -1,   -1,   -1,   -1,   -1,  278,  279,   -1,   -1,   -1,
   -1,  280,  272,  273,  274,  275,  276,  277,   -1,   -1,
   -1,   -1,  282,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  280,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 283
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"Character_String","Function",
"Identifier","Integer","Real","CONSTANTS","MAIN","FUNCTIONS","Return","Read",
"Print","If","Then","Else","While","EQ","NEQ","GTE","LTE","GT","LT","Loop",
"Assign","Lbracket","Rbracket","Boolean","\"end of file\"",
};
char *yyrule[] = {
"$accept : program",
"program : CONSTANTS_ constant_defs FUNCTIONS_ function_defs MAIN_ statements END",
"CONSTANTS_ : CONSTANTS",
"FUNCTIONS_ : FUNCTIONS",
"MAIN_ : MAIN",
"Lbracket_ : Lbracket",
"Rbracket_ : Rbracket",
"constant_defs :",
"constant_defs : constant_defs constant_def",
"constant_def : Lbracket_ Identifier Sparam Rbracket_",
"Sparam : Number",
"Sparam : Boolean",
"Sparam : Character_String",
"Number : Integer",
"Number : Real",
"function_defs :",
"function_defs : function_defs function_def",
"function_def : Fixme Identifier Args Return Identifier statements Rbracket_",
"Fixme : Lbracket_",
"Args : Identifier",
"Args : Identifier Args",
"statements :",
"statements : statements statement",
"statement : assignmentstatement",
"statement : readstatement",
"statement : printstatement",
"statement : ifstatement",
"statement : loopstatement",
"statement : whilestatement",
"assignmentstatement : Lbracket_ Assign_ Identifier AParameter Rbracket_",
"Assign_ : Assign",
"AParameter : Parameter",
"Parameter : FunctionCall",
"Parameter : Identifier",
"Parameter : Number",
"PFPFix :",
"FunctionCall : FLbracket_ FParams Rbracket_",
"FunctionCall : Lbracket_ Function PFPFix PFParam Rbracket_",
"FunctionCall : Lbracket_ Function PFPFix PFParam Hotfix Rbracket_",
"FunctionCall : PF2 PFParams Rbracket_",
"Hotfix : PFParam",
"PFParams : PFParam",
"PFParams : PFParam PFParams",
"PF2 : Lbracket_ Function PFPFix PFParam PFParam",
"PFParam : FunctionCall",
"PFParam : Identifier",
"PFParam : Number",
"FLbracket_ : Lbracket_ Identifier",
"FPFix :",
"FParams : FPFix Parameter FParams",
"FParams : FPFix Parameter",
"readstatement : Lbracket_ Read RID Rbracket_",
"RID : Identifier",
"RID : RID Identifier",
"printstatement : Lbracket_ Print PrintParams Rbracket_",
"PrintParams : PrintParam",
"PrintParams : PrintParams PrintParam",
"PrintParam : Identifier",
"PrintParam : Sparam",
"ifstatement : Lbracket_ If SExpn Then_ statements Else_ statements Rbracket_",
"SExpn : Expn",
"Then_ : Then",
"Else_ : Else",
"loopstatement : Lbracket_ Loop_ statements Rbracket_",
"Loop_ : Loop Identifier",
"whilestatement : Lbracket_ While_ statements Rbracket_",
"While_ : While Expn",
"Expn : Lbracket_ CompOp Parameter Parameter Rbracket_",
"Expn : Lbracket_ Boolean Rbracket_",
"CompOp : EQ",
"CompOp : NEQ",
"CompOp : GTE",
"CompOp : LTE",
"CompOp : GT",
"CompOp : LT",
};
#endif
#if YYDEBUG
#include <stdio.h>
#endif

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 500

int      yydebug;
int      yynerrs;
int      yyerrflag;
int      yychar;
short   *yyssp;
YYSTYPE *yyvsp;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* variables for the parser stack */
static short   *yyss;
static short   *yysslim;
static YYSTYPE *yyvs;
static int      yystacksize;
#line 1234 "FP.yacc"

void yyerror(char* s) {
	printf("%s on or after line %d\n", s, ln);

	printInstructions();
	exit(-1);
}

int yywrap() {
	return 1;
}

int main(int argc, char* argv[]) { 

#ifdef YYMJDEBUG 	
	yydebug = 1;
#endif
	if (argc != 2) {
		printf("Usage: %s <mc_output_filename> < <INPUT_FILE>\n", argv[0]);
		exit(-1);
	}
	outfile.open(argv[1], ofstream::out);
	instructions.push_back("goto MAIN;");
	yyparse();

	patch();
	printInstructions();

	// DEBUG
	printSymbolTable();
	
	outfile.close();
}

void printInstructions() {
	int i;
	for (i = 0; i < instructions.size(); i++) {
		outfile << instructions.at(i) << endl;
	}
}

int findSymbolIndex(string s) {
	int i = 0;
	for (; i < num_syms; i++) {
		if (sym_table[i].arr[1] == s) {
			return i;
		}
	}
	return -1;
}

void addToTable(Symbol s) {
	if (num_syms >= MAX_SYMBOLS) {
		yyerror("Too many symbols. Exiting...");
	} else if (findSymbolIndex(s.arr[1]) == -1) {
		sym_table[num_syms] = s;
		num_syms++;
	} else {
		yyerror("Redefinition of symbol not allowed!");
	}
}

void patch() {
	int i;

	int func = -1;
	for (i = 0; i < num_syms; i++) {
		if (sym_table[i].arr[0] == "function") {
			func = i;
			break;
		}
	}
	if (func == -1) {
		return;
	}
	for (i = 0; i < instructions.size(); i++) {
		if (instructions.at(i) == "goto 0;") {
			stringstream ss;
			ss << "goto " << sym_table[func].arr[3] << ";";
			instructions.at(i) = ss.str();
			ss.str("");

			func = -1;
			int j;
			for (j = func+1; j < num_syms; j++) {
				if(sym_table[j].arr[0] == "function") {
					func = j;
					break;
				}
			}

			
			
		}
	}
}


void printSymbolTable()
{
	printf("SYMBOL TABLE:\n");
	int i = 0;
	for (; i < num_syms; i++) {
		cout << i << "\t";
		Symbol t = sym_table[i];
		if (GetType(t) == "constant") {
			cout << "const\tid: " << GetName(t) << "\ttype: " << sym_table[i].arr[2] << "\tval: " << sym_table[i].arr[3] << endl;
		} else if (GetType(t) == "variable") {
			cout << "var\tid: " << GetName(t) << "\tM-addr: " << sym_table[i].arr[2] << "\t# times used/defined: " << sym_table[i].arr[3] << endl;
		} else if (GetType(t) == "function") {
			cout << "func\tid: " << GetName(t) << "\tindex of 1st instr: " << sym_table[i].arr[2] << "\tret_addr: " << sym_table[i].arr[3] << 
				"\t# of callers: " << sym_table[i].arr[4] << endl;
		}
	}
}

#line 510 "y.tab.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(void)
{
    int newsize, i;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = yyssp - yyss;
    newss = (yyss != 0)
          ? (short *)realloc(yyss, newsize * sizeof(*newss))
          : (short *)malloc(newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    yyss  = newss;
    yyssp = newss + i;
    newvs = (yyvs != 0)
          ? (YYSTYPE *)realloc(yyvs, newsize * sizeof(*newvs))
          : (YYSTYPE *)malloc(newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse(void)
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

#ifdef lint
    goto yyerrlab;
#endif

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yyvsp[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 89 "FP.yacc"
{
		instructions.at(0) = createGoto(yyvsp[-2].num+1); 
		/* TODO*/
		/*if ($5+1 == $6) {*/
			instructions.push_back("mul R0 1;");
		/*}*/
		return 1;
	}
break;
case 2:
#line 99 "FP.yacc"
{
	ln = yyvsp[0].lineNum;
	}
break;
case 3:
#line 103 "FP.yacc"
{
	ln = yyvsp[0].lineNum; 
}
break;
case 4:
#line 107 "FP.yacc"
{ ln = yyvsp[0].lineNum; yyval.num = instructions.size(); }
break;
case 5:
#line 109 "FP.yacc"
{
	ln = yyvsp[0].lineNum;
}
break;
case 6:
#line 113 "FP.yacc"
{
	ln = yyvsp[0].lineNum;
}
break;
case 8:
#line 119 "FP.yacc"
{

	}
break;
case 9:
#line 125 "FP.yacc"
{
		Symbol s;
		s.arr[0] = "constant";
		char* res = (char*)(malloc(strlen(yyvsp[-2].char_string)+1));
		strcpy(res, yyvsp[-2].char_string);
		s.arr[1] = res;
		if (yyvsp[-1].num == REAL) {
			s.arr[2] = "real";
			stringstream ss;
			ss << sp.n;
			s.arr[3] = ss.str();
		} else if (yyvsp[-1].num == INTEGER) {
			s.arr[2] = "integer";
			stringstream ss;
			ss << sp.n;
			s.arr[3] = ss.str();
		} else if (yyvsp[-1].num == BOOLEAN) {
			s.arr[2] = "boolean";

			if (sp.b) {
				s.arr[3] = "T";
			} else {
				s.arr[3] = "F";
			}
		} else if (yyvsp[-1].num == CHAR_STRING) {
			s.arr[2] = "char_str";
			s.arr[3] = sp.c;
		}
		addToTable(s);
	}
break;
case 10:
#line 158 "FP.yacc"
{
		yyval.num = yyvsp[0].num;
	}
break;
case 11:
#line 161 "FP.yacc"
{
		yyval.num = BOOLEAN;
		sp.b = yyvsp[0].bval;
	}
break;
case 12:
#line 165 "FP.yacc"
{
		yyval.num = CHAR_STRING; 
		sp.c = yyvsp[0].char_string;
	}
break;
case 13:
#line 172 "FP.yacc"
{
		yyval.num = INTEGER;
		sp.n = yyvsp[0].num;
	}
break;
case 14:
#line 176 "FP.yacc"
{
		yyval.num = REAL;
		sp.n = yyvsp[0].num;
	}
break;
case 15:
#line 183 "FP.yacc"
{
		yyval.num = instructions.size();
	}
break;
case 16:
#line 187 "FP.yacc"
{
		yyval.num = instructions.size();
	}
break;
case 17:
#line 193 "FP.yacc"
{
		Symbol s;
		s.arr[0] = "function";

		char* res = (char*)(malloc(strlen(yyvsp[-5].char_string)+1));
		strcpy(res, yyvsp[-5].char_string);
		s.arr[1] = res;
		
		stringstream ss;
		ss << yyvsp[-6].num;
		s.arr[2] = ss.str();
		ss.str("");
		ss << 1;
		s.arr[3] = ss.str();
		ss.str("");
		ss << 0;
		s.arr[4] = ss.str();
		s.ret = yyvsp[-2].char_string;

		while (!args.empty()) {
			s.vars.push_back(args.front());
			args.erase(args.begin());
		}

		addToTable(s);
		instructions.push_back(createGoto(0));

	}
break;
case 18:
#line 224 "FP.yacc"
{
		yyval.num = instructions.size()+1;
	}
break;
case 19:
#line 230 "FP.yacc"
{
		if (m_addr < MAX_M_ADDR) {
			Symbol s;
			s.arr[0] = "variable";
			s.arr[1] = yyvsp[0].char_string;
			stringstream ss;
			ss << m_addr;
			s.arr[2] = ss.str();
			s.arr[3] = "1";
			args.push_back(yyvsp[0].char_string);
			addToTable(s);
			m_addr++;
		} else {
			yyerror("M_Addr list full. Exiting");
		}

	}
break;
case 20:
#line 248 "FP.yacc"
{

		vector<string> vars;
		if (m_addr < MAX_M_ADDR) {
			Symbol s;
			s.arr[0] = "variable";
			s.arr[1] = yyvsp[-1].char_string;
			stringstream ss;
			ss << m_addr;
			s.arr[2] = ss.str();
			s.arr[3] = "1";
			args.push_back(yyvsp[-1].char_string);
			addToTable(s);
			m_addr++;
		} else {
			yyerror("M_Addr list full. Exiting");
		}
	}
break;
case 21:
#line 267 "FP.yacc"
{
		yyval.num = instructions.size();
	}
break;
case 22:
#line 271 "FP.yacc"
{
		yyval.num = instructions.size();
	}
break;
case 23:
#line 277 "FP.yacc"
{
		yyval.num = yyvsp[0].num;
	}
break;
case 24:
#line 281 "FP.yacc"
{
		yyval.num = yyvsp[0].num;
	}
break;
case 25:
#line 285 "FP.yacc"
{
		yyval.num = yyvsp[0].num;
	}
break;
case 26:
#line 289 "FP.yacc"
{
		yyval.num = yyvsp[0].num;
	}
break;
case 27:
#line 293 "FP.yacc"
{
		yyval.num = yyvsp[0].num;
	}
break;
case 28:
#line 297 "FP.yacc"
{
		yyval.num = yyvsp[0].num;
	}
break;
case 29:
#line 303 "FP.yacc"
{

		int index = findSymbolIndex(yyvsp[-2].char_string);
		if (index == -1) {
			Symbol s;
			s.arr[0] = "variable";
			s.arr[1] = yyvsp[-2].char_string;
			if (m_addr >= MAX_M_ADDR) {
				yyerror("Too many variables. Exiting");
			}
			stringstream oss;
			oss << m_addr;
			s.arr[2] = oss.str();
			s.arr[3] = "1";
			addToTable(s);
			m_addr++;
		} else if (sym_table[index].arr[0] == "constant") {
			yyerror("Cannot redefine constant! Exiting");
		} else if (sym_table[index].arr[0] == "function") {
			yyerror("Cannot assign to existing function. Exiting");
		} else {
			int tmp;
			stringstream ss;
			ss << sym_table[index].arr[3];
			ss >> tmp;
			tmp++;
			ss.str("");
			ss.clear();
			ss << tmp;
			ss >> sym_table[index].arr[3];
		}
		index = findSymbolIndex(yyvsp[-2].char_string);

		int v = yyvsp[-1].num;
		stringstream ss;

		if (sp.fnc == 1) {
			int rt = sp.func;
			v = findRegister();
			ss << "load R" << v << " M" << rt << ";";
			instructions.push_back(ss.str());
			sp.fnc = -1;
			ss.str("");
			ss.clear();
		}
		ss << "store R" << v << " M" << sym_table[index].arr[2] << ";";
		
		instructions.push_back(ss.str());
		freeRegister(v);
		
	}
break;
case 30:
#line 357 "FP.yacc"
{
		ln = yyvsp[0].lineNum;
	}
break;
case 31:
#line 363 "FP.yacc"
{
		int reg = yyvsp[0].num;
		yyval.num = yyvsp[0].num;
	}
break;
case 32:
#line 369 "FP.yacc"
{

		int reg = yyvsp[0].num;
		yyval.num = reg;
		sp.n = 1;
	}
break;
case 33:
#line 376 "FP.yacc"
{


		sp.fnc = -1;
		int index = findSymbolIndex(yyvsp[0].char_string);
		
		if (index == -1) {
			yyerror("Symbol not found. Exiting");
		}
		if (sym_table[index].arr[0] == "function") {
			yyerror("Cannot assign function to variable. Exiting");
		} else if (sym_table[index].arr[0] == "constant") {
			string tp = sym_table[index].arr[2];
			if (tp == "char_str") {
				yyerror("Invalid parameter");
			}
			int reg = findRegister();
			if (tp != "boolean") {
				stringstream ss;
				ss << "load R" << reg << " " << sym_table[index].arr[3] << ";";
				instructions.push_back(ss.str());
				sp.n = 1;
			} else {
				stringstream ss;
				if (sym_table[index].arr[3] == "T") {
					ss << "load R" << reg << " 1;";
					instructions.push_back(ss.str());
				} else {
					ss << "load R" << reg << " 0;";
					instructions.push_back(ss.str());
				}
				sp.n = 0;
			}
			claimRegister(reg);
			yyval.num = reg;
			
		} else if (sym_table[index].arr[0] == "variable") {
			stringstream ss;
			ss << sym_table[index].arr[3];
			int val;
			ss >> val;
			val++;
			ss.str("");
			ss.clear();
			ss << val;
			sym_table[index].arr[3] = val;
			ss.str("");
			ss.clear();
			
			int reg = findRegister();
			ss << "load R" << reg << " M" << sym_table[index].arr[2] << ";";
			instructions.push_back(ss.str());
			claimRegister(reg);
			yyval.num = reg;
			sp.n = 1;
		}

	}
break;
case 34:
#line 435 "FP.yacc"
{
		
		int reg = findRegister();
		stringstream ss;
		ss << "load R" << reg << " " << sp.n << ";";
		instructions.push_back(ss.str());
		claimRegister(reg);
		yyval.num = reg;
		sp.n = 1;
		sp.fnc = -1;
	}
break;
case 35:
#line 449 "FP.yacc"
{
		instructions.push_back(instructions.back());
	}
break;
case 36:
#line 455 "FP.yacc"
{
		int index = yyvsp[-2].num;

		stringstream ss;
		ss.str("");
		ss << sym_table[index].arr[4];
		int calls;
		ss >> calls;
		if (calls == 1) {
			yyerror("Function may only be called once");
		} else {
			sym_table[index].arr[4] = "1";
		}
		ss.str("");
		ss.clear();

		ss << "goto " << sym_table[index].arr[2] << ";";
		instructions.push_back(ss.str());

		ss.str("");
		ss.clear();
		int ret = instructions.size()+1;
		ss << ret;
		sym_table[index].arr[3] = ss.str();

		yyval.num = yyvsp[-1].num;

		sp.func = findSymbolIndex(sym_table[index].ret);
		sp.fnc = 1;
	}
break;
case 37:
#line 486 "FP.yacc"
{
		string str = yyvsp[-3].char_string;
		str = str.substr(0,2);
		if (str == "**") {
			int reg = yyvsp[-1].num;
			stringstream ss;
			ss << "square R" << reg << ";";
			instructions.push_back(ss.str());
			yyval.num = reg;
		} else {
			yyerror("Pre-defined functions other than ** require more than 1 param");
		}
		sp.fnc = -1;
	}
break;
case 38:
#line 501 "FP.yacc"
{


		string op;

		string t = yyvsp[-4].char_string;
		t = t.substr(0, 2);
		if (t == "**") {
			yyerror("Pre-defined function ** only takes one param");
		} else if (t.at(0) == '*') {
			op = "mul";
		} else if (t.at(0) == '/') {
			op = "div";
		} else if (t.at(0) == '-') {
			op = "sub";
		} else if (t.at(0) == '+') {
			op = "add";
		}
		stringstream ss;
		ss << op << " R" << yyvsp[-2].num << " R" << yyvsp[-1].num << ";";
		instructions.push_back(ss.str());
		freeRegister(yyvsp[-1].num);
		yyval.num = yyvsp[-2].num;
		sp.fnc = -1;
		
	}
break;
case 39:
#line 527 "FP.yacc"
{
		string op = instructions.back();
		stringstream ss;
		ss << op << " R" << yyvsp[-2].num << " R" << yyvsp[-1].num << ";";
		instructions.pop_back();
		instructions.push_back(ss.str());

		freeRegister(yyvsp[-1].num);
		yyval.num = yyvsp[-2].num;

		sp.fnc = -1;
		
	}
break;
case 40:
#line 543 "FP.yacc"
{
		instructions.pop_back();
		yyval.num = yyvsp[0].num;
	}
break;
case 41:
#line 549 "FP.yacc"
{
		yyval.num = yyvsp[0].num;
		
	
	}
break;
case 42:
#line 555 "FP.yacc"
{
		string op = instructions.at(instructions.size()-1);
		stringstream ss;
		ss << op << " R" << yyvsp[-1].num << " R" << yyvsp[0].num << ";";

		instructions.at(instructions.size()-1) = ss.str();
		instructions.push_back(op);
		

		freeRegister(yyvsp[0].num);
		yyval.num = yyvsp[-1].num;
		
	}
break;
case 43:
#line 571 "FP.yacc"
{
		stringstream ss;
		ss << yyvsp[-3].char_string[0];
		string op;
		ss >> op;
		if (op == "*") {
			op = "mul";
		} else if (op == "+") {
			op = "add";
		} else {
			yyerror("Only pre-defined functions + and * can take more than 2 parameters");
		}
		ss.str("");
		ss.clear();
		ss << op << " R" << yyvsp[-1].num << " R" << yyvsp[0].num << ";";
		instructions.pop_back();
		instructions.push_back(ss.str());
		instructions.push_back(op);
		freeRegister(yyvsp[0].num);
		yyval.num = yyvsp[-1].num;
	}
break;
case 44:
#line 595 "FP.yacc"
{
		string op = instructions.back();
		
		stringstream ss;
		instructions.pop_back();
		instructions.push_back(op);

		yyval.num = yyvsp[0].num;
	}
break;
case 45:
#line 605 "FP.yacc"
{

		int index = findSymbolIndex(yyvsp[0].char_string);
		string op = instructions.back();
		
		if (index == -1) {
			yyerror("Symbol not found. Exiting");
		}
		if (sym_table[index].arr[0] == "function") {
			yyerror("Cannot assign function to variable. Exiting");
		} else if (sym_table[index].arr[0] == "constant") {
			string tp = sym_table[index].arr[2];
			if (tp == "char_str") {
				yyerror("Character string cannot be passed to pre-defined function");
			}
			int reg = findRegister();
			if (tp != "boolean") {
				stringstream ss;
				ss << "load R" << reg << " " << sym_table[index].arr[3] << ";";
				instructions.at(instructions.size()-1) = ss.str();
				
				instructions.push_back(op);
			} else {
				yyerror("Boolean value cannot be passed to pre-defined function");
			}
			claimRegister(reg);
			yyval.num = reg;
			
		} else if (sym_table[index].arr[0] == "variable") {
			stringstream ss;
			ss << sym_table[index].arr[3];
			int val;
			ss >> val;
			val++;
			ss.str("");
			ss.clear();
			ss << val;
			sym_table[index].arr[3] = val;
			ss.str("");
			ss.clear();
			
			int reg = findRegister();
			ss << "load R" << reg << " M" << sym_table[index].arr[2] << ";";
			instructions.back() = ss.str();
			instructions.push_back(op);
			claimRegister(reg);
			yyval.num = reg;
		}
	}
break;
case 46:
#line 655 "FP.yacc"
{

		int reg = findRegister();
		stringstream ss;
		ss << "load R" << reg << " " << sp.n << ";";
		string op = instructions.back();
		instructions.back() = ss.str();
		instructions.push_back(op);
		claimRegister(reg);
		yyval.num = reg;
	}
break;
case 47:
#line 669 "FP.yacc"
{
		int index = findSymbolIndex(yyvsp[0].char_string);
		if (index == -1) {
			yyerror("Cannot call undefined function");
		} else if (sym_table[index].arr[0] != "function") {
			yyerror("Identifier in function call is not a function");
		}
		stringstream ss;
		ss << index;
		instructions.push_back(ss.str());
		
		yyval.num = index;
	}
break;
case 48:
#line 685 "FP.yacc"
{
		if (fix == -1) {
			int index;
			stringstream ss;
			ss << instructions.back();
			ss >> index;
			yyval.num = index;
			fix = index;
			instructions.pop_back();
		} else {
			yyval.num = fix;
		}
	}
break;
case 49:
#line 703 "FP.yacc"
{
		int index = yyvsp[-2].num;
		stringstream ss;

		if (sym_table[index].vars.size() < 1) {
			yyerror("Improper number of parameters to function call");
		}
		
		string var = sym_table[index].vars.front();
		sym_table[index].vars.erase(sym_table[index].vars.begin(), sym_table[index].vars.begin()+1);

		int i = findSymbolIndex(var);
		string addr = sym_table[i].arr[2];

		ss << sym_table[i].arr[3];
		ss >> index;
		index++;
		
		ss.str("");
		ss.clear();
		ss << index;
		sym_table[i].arr[3] = ss.str();
		ss.str("");
		ss.clear();

		int reg = yyvsp[-1].num;
		freeRegister(reg);
		ss << "store R" << reg << " M" << addr << ";";
		instructions.push_back(ss.str());
	}
break;
case 50:
#line 733 "FP.yacc"
{
		int index = yyvsp[-1].num;
		stringstream ss;

		if (sym_table[index].vars.size() < 1) {
			yyerror("Improper number of parameters to function call");
		}
		
		string var = sym_table[index].vars.front();
		sym_table[index].vars.erase(sym_table[index].vars.begin(), sym_table[index].vars.begin()+1);

		int i = findSymbolIndex(var);
		string addr = sym_table[i].arr[2];

		ss << sym_table[i].arr[3];
		ss >> index;
		index++;
		
		ss.str("");
		ss.clear();
		ss << index;
		sym_table[i].arr[3] = ss.str();
		ss.str("");
		ss.clear();

		int reg = yyvsp[0].num;
		freeRegister(reg);
		ss << "store R" << reg << " M" << addr << ";";
		instructions.push_back(ss.str());
		fix = -1;

	}
break;
case 51:
#line 810 "FP.yacc"
{
		stringstream ss;
		ss << "read " << yyvsp[-1].char_string << ";";
		instructions.push_back(ss.str());
	}
break;
case 52:
#line 819 "FP.yacc"
{
		int index = findSymbolIndex(yyvsp[0].char_string);
		if (index == -1) {
			Symbol s;
			s.arr[0] = "variable";
			s.arr[1] = yyvsp[0].char_string;
			stringstream ss;
			ss << m_addr;
			s.arr[2] = ss.str(); 
			if (m_addr >= MAX_M_ADDR) {
				yyerror("Too many variables!");
			}
			m_addr++;
			s.arr[3] = "1";
			addToTable(s);
			index = findSymbolIndex(yyvsp[0].char_string);
			ss.str("");
			ss << "M" << sym_table[index].arr[2];

			string t = ss.str();
			char* res = (char*)(malloc(t.length()+1));
			strcpy(res, t.c_str());
			yyval.char_string = res;
		} else if (sym_table[index].arr[0] == "variable") {
			stringstream ss;
			ss << "M" << sym_table[index].arr[2];

			string t = ss.str();
			char* res = (char*)(malloc(t.length()+1));
			strcpy(res, t.c_str());
			yyval.char_string = res;
		} else {
			yyerror("Cannot redefine constant or function!");
		}
	}
break;
case 53:
#line 855 "FP.yacc"
{
		int index = findSymbolIndex(yyvsp[0].char_string);
		if (index == -1) {
			Symbol s;
			s.arr[0] = "variable";
			s.arr[1] = yyvsp[0].char_string;
			stringstream ss;
			ss << m_addr;
			s.arr[2] = ss.str(); 
			if (m_addr >= MAX_M_ADDR) {
				yyerror("Too many variables!");
			}
			m_addr++;
			s.arr[3] = "1";
			addToTable(s);
			index = findSymbolIndex(yyvsp[0].char_string);
			ss.str("");
			ss << yyvsp[-1].char_string << " M" << sym_table[index].arr[2];
			
			string t = ss.str();
			char* res = (char*)(malloc(t.length()+1));
			strcpy(res, t.c_str());
			yyval.char_string = res;

		} else if (sym_table[index].arr[0] == "variable") {

			stringstream ss;
			ss << yyvsp[-1].char_string << " M" << sym_table[index].arr[2];

			string t = ss.str();
			char* res = (char*)(malloc(t.length()+1));
			strcpy(res, t.c_str());
			yyval.char_string = res;
		} else {
			yyerror("Cannot redefine constant or function!");
		}

	}
break;
case 54:
#line 895 "FP.yacc"
{
		stringstream ss;
		ss << "print " << yyvsp[-1].char_string << ";";
		instructions.push_back(ss.str());
		
	}
break;
case 55:
#line 904 "FP.yacc"
{
		yyval.char_string = yyvsp[0].char_string;
	}
break;
case 56:
#line 908 "FP.yacc"
{
		stringstream ss;
		ss << yyvsp[-1].char_string << " " << yyvsp[0].char_string;
		string t = ss.str();
		char* res = (char*)(malloc(t.length()+1));
		strcpy(res, t.c_str());
		yyval.char_string = res;
	}
break;
case 57:
#line 919 "FP.yacc"
{
		int index = findSymbolIndex(yyvsp[0].char_string);
		if (index == -1) {
			yyerror("Cannot print non-existent identifier");
		} else if (sym_table[index].arr[0] == "function") {
			yyerror("Cannot print a function");
		} else if (sym_table[index].arr[0] == "variable") {
			stringstream ss;
			ss << sym_table[index].arr[3];
			int t;
			ss >> t;
			t++;
			ss.str("");
			ss.clear();
			ss << t;
			sym_table[index].arr[3] = ss.str();
			
			ss.str("");
			ss.clear();
			string z = sym_table[index].arr[2];
			ss << "M" << z;
			z = ss.str();
			
			char* res = (char*)(malloc(z.length()+1));
			strcpy(res, z.c_str());
			yyval.char_string = res;
		} else if (sym_table[index].arr[0] == "constant") {
			stringstream ss;

			ss << sym_table[index].arr[3];
			string z = ss.str();
			
			char* res = (char*)(malloc(z.length()+1));
			strcpy(res, z.c_str());
			yyval.char_string = res;
		}
	}
break;
case 58:
#line 957 "FP.yacc"
{
		int s = yyvsp[0].num;

		if (s == NUMBER) {
			stringstream ss;
			ss << sp.n;
			string z = ss.str();
			char* res = (char*)(malloc(z.length()+1));
			strcpy(res, z.c_str());
			yyval.char_string = res;
		} else if (s == BOOLEAN) {
			string z = "0";
			if (sp.b) {
				z = "1";
			}
			char* res = (char*)(malloc(z.length()+1));
			strcpy(res, z.c_str());
			yyval.char_string = res;
		} else if (s == CHAR_STRING) {
			char* res = (char*)(malloc(sp.c.length()+1));
			strcpy(res, sp.c.c_str());
			yyval.char_string = res;
		}
	}
break;
case 59:
#line 984 "FP.yacc"
{

		int v = yyvsp[-5].num;
		int nr = findRegister();

		int istr = yyvsp[-4].num;
		stringstream ss;
		ss << "load R" << nr << "M" << v << ";";
		instructions.at(istr) = ss.str();
		ss.str("");
		ss.clear();
		ss << "if R" << v << " " << istr+3 << ";";
		instructions.at(istr+1) = ss.str(); 
		ss.str("");
		ss.clear();
		int t = yyvsp[-2].num+2;
		instructions.at(istr+2) = createGoto(t);
		ss << "goto " << yyvsp[-1].num+1 << ";";
		
		int a = yyvsp[-2].num;
		instructions.at(a) = (ss.str());
	}
break;
case 60:
#line 1009 "FP.yacc"
{
		int v = yyvsp[0].num;
		freeRegister(v);
		if (m_addr < MAX_M_ADDR) {
			stringstream ss;
			ss << "store R" << v << " M" << m_addr << ";";
			instructions.push_back(ss.str());
			yyval.num = m_addr;
			m_addr++;
		} else {
			yyerror("Out of memory addresses");
		}
		
	}
break;
case 61:
#line 1025 "FP.yacc"
{

	yyval.num = instructions.size();
	instructions.push_back("dummy");
	instructions.push_back("dummy");
	instructions.push_back("dummy");

}
break;
case 62:
#line 1034 "FP.yacc"
{
	yyval.num = instructions.size();
	instructions.push_back("dummy");
}
break;
case 63:
#line 1040 "FP.yacc"
{
		stringstream ss;
		ss << instructions.at(yyvsp[-2].num);
		int reg;
		ss >> reg;


		stringstream ss1;
		ss1 << "goto " << yyvsp[-1].num+2 << ";";
		instructions.at(yyvsp[-2].num) = ss1.str();
		ss1.str("");
		ss1 << "goto " << yyvsp[-2].num << ";";
		instructions.push_back(ss1.str());
		ss1.str("");
		/*ss1 << "mul R1 1;";*/
		/*instructions.push_back(ss1.str());*/
		freeRegister(reg);
		
	}
break;
case 64:
#line 1062 "FP.yacc"
{
		int reg = findRegister();
		claimRegister(reg);
		int index = findSymbolIndex(yyvsp[0].char_string);

		if (sym_table[index].arr[0] == "constant" && sym_table[index].arr[2] == "integer") {
			stringstream ss;
			ss << "load R" << reg << " " << sym_table[index].arr[3] << ";";
			instructions.push_back(ss.str());
			ss.str("");
			ss << "if R" << reg << " " << (instructions.size()+3) << ";";
			instructions.push_back(ss.str());
			yyval.num = instructions.size();
			ss.str("");
			ss << reg;
			instructions.push_back(ss.str());
			ss.str("");
			ss << "sub R" << reg << " 1;";
			instructions.push_back(ss.str());
		} else if (sym_table[index].arr[0] == "variable") {
			stringstream ss;
			ss << "load R" << reg << " M" << sym_table[index].arr[2] << ";";
			
			instructions.push_back(ss.str());
			ss.str("");
			ss << "if R" << reg << " " << (instructions.size()+3) << ";";
			instructions.push_back(ss.str());
			yyval.num = instructions.size();
			ss.str("");
			ss << reg;
			instructions.push_back(ss.str());
			ss.str("");
			ss << "sub R" << reg << " 1;";
			instructions.push_back(ss.str());
			ss.str("");
			ss.clear();
			ss << sym_table[index].arr[2];
			int used;
			ss >> used;
			used++;
			ss.str("");
			ss.clear();
			ss << used;
			sym_table[index].arr[2] = ss.str();
		} else {
			yyerror("Loop var must be an integer");
		}
	}
break;
case 65:
#line 1113 "FP.yacc"
{

		stringstream ss;
		ss << instructions.at(yyvsp[-2].num);
		int reg;
		ss >> reg;
		ss.str("");
		ss.clear();
		ss << "goto " << yyvsp[-1].num+2 << ";";
		instructions.at(yyvsp[-2].num) = ss.str();
		ss.str("");
		ss.clear();
		int sz = yyvsp[-2].num-3;
		ss << "goto " << sz << ";";
		instructions.push_back(ss.str());
		
		freeRegister(reg);
		
	}
break;
case 66:
#line 1136 "FP.yacc"
{

		stringstream ss;
		int sz = instructions.size()+3;
		ss << "if R" << yyvsp[0].num << " " << sz << ";";
		instructions.push_back(ss.str());

		ss.str("");
		ss.clear();
		ss << yyvsp[0].num;
		yyval.num = instructions.size();
		instructions.push_back(ss.str());


	}
break;
case 67:
#line 1154 "FP.yacc"
{
		int reg0 = findRegister();
		claimRegister(reg0);
		int reg1 = yyvsp[-2].num;
		int reg2 = yyvsp[-1].num;

		stringstream ss;
		ss << yyvsp[-3].char_string << " R" << reg0 << " R" << reg1 << " R" << reg2 << ";";
		instructions.push_back(ss.str());


		freeRegister(reg2);
		freeRegister(reg1);
		yyval.num = reg0;
	}
break;
case 68:
#line 1170 "FP.yacc"
{
		int reg = findRegister();
		claimRegister(reg);

		string z = "0";
		if (yyvsp[-1].bval) {
			z = "1";
		}
		stringstream ss;
		ss << "load R" << reg << " " << z << ";";
		instructions.push_back(ss.str());

		yyval.num = reg;
	}
break;
case 69:
#line 1187 "FP.yacc"
{
		string s = "==";
		char* res = (char*)(malloc(s.length()+1));
		strcpy(res, s.c_str());
		yyval.char_string = res;
	}
break;
case 70:
#line 1194 "FP.yacc"
{
		string s = "!=";
		char* res = (char*)(malloc(s.length()+1));
		strcpy(res, s.c_str());
		yyval.char_string = res;

	}
break;
case 71:
#line 1202 "FP.yacc"
{
		string s = ">=";
		char* res = (char*)(malloc(s.length()+1));
		strcpy(res, s.c_str());
		yyval.char_string = res;

	}
break;
case 72:
#line 1210 "FP.yacc"
{
		string s = "<=";
		char* res = (char*)(malloc(s.length()+1));
		strcpy(res, s.c_str());
		yyval.char_string = res;
	}
break;
case 73:
#line 1217 "FP.yacc"
{
		string s = ">";
		char* res = (char*)(malloc(s.length()+1));
		strcpy(res, s.c_str());
		yyval.char_string = res;
	}
break;
case 74:
#line 1223 "FP.yacc"
{
		string s = "<";
		char* res = (char*)(malloc(s.length()+1));
		strcpy(res, s.c_str());
		yyval.char_string = res;
	}
break;
#line 1870 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    return (1);

yyaccept:
    return (0);
}
