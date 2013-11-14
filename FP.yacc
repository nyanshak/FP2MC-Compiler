%{
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
%}

%union {
	float num;
	char* char_string;
	bool bval;
	int lineNum;
}

%token <char_string> Character_String Function Identifier
%token <num> Integer Real
%token <lineNum> CONSTANTS MAIN FUNCTIONS Return Read Print If Then Else While EQ NEQ GTE LTE GT LT Loop Assign Print Lbracket Rbracket
%token <bval> Boolean
%token END 0 "end of file"

%type <num> Sparam statements Number Parameter FunctionCall Expn SExpn statement assignmentstatement readstatement printstatement ifstatement whilestatement loopstatement Then_ Loop_ MAIN_ function_defs While_ FParams FLbracket_ PFParam PFParams PF2 Else_ FPFix Hotfix Fixme AParameter
%type <char_string> RID PrintParams PrintParam CompOp
%start program

%%

program:	CONSTANTS_ constant_defs FUNCTIONS_ function_defs MAIN_ statements END
	{
		instructions.at(0) = createGoto($5+1); 
		// TODO
		//if ($5+1 == $6) {
			instructions.push_back("mul R0 1;");
		//}
		return 1;
	}
	;

CONSTANTS_: CONSTANTS {
	ln = $1;
	};

FUNCTIONS_: FUNCTIONS {
	ln = $1; 
};

MAIN_: MAIN { ln = $1; $$ = instructions.size(); };

Lbracket_: Lbracket {
	ln = $1;
};

Rbracket_: Rbracket {
	ln = $1;
};

constant_defs:	/* empty */
	| constant_defs constant_def
	{

	}
	;

constant_def: Lbracket_ Identifier Sparam Rbracket_
	{
		Symbol s;
		s.arr[0] = "constant";
		char* res = (char*)(malloc(strlen($2)+1));
		strcpy(res, $2);
		s.arr[1] = res;
		if ($3 == REAL) {
			s.arr[2] = "real";
			stringstream ss;
			ss << sp.n;
			s.arr[3] = ss.str();
		} else if ($3 == INTEGER) {
			s.arr[2] = "integer";
			stringstream ss;
			ss << sp.n;
			s.arr[3] = ss.str();
		} else if ($3 == BOOLEAN) {
			s.arr[2] = "boolean";

			if (sp.b) {
				s.arr[3] = "T";
			} else {
				s.arr[3] = "F";
			}
		} else if ($3 == CHAR_STRING) {
			s.arr[2] = "char_str";
			s.arr[3] = sp.c;
		}
		addToTable(s);
	}
	;

Sparam:
	Number {
		$$ = $1;
	}
	| Boolean {
		$$ = BOOLEAN;
		sp.b = $1;
	}
	| Character_String {
		$$ = CHAR_STRING; 
		sp.c = $1;
	}
	;

Number:
	Integer {
		$$ = INTEGER;
		sp.n = $1;
	}
	| Real {
		$$ = REAL;
		sp.n = $1;
	}
	;

function_defs:	/* empty */
	{
		$$ = instructions.size();
	}
	| function_defs function_def
	{
		$$ = instructions.size();
	}
	;

function_def: Fixme Identifier Args Return Identifier statements Rbracket_
	{
		Symbol s;
		s.arr[0] = "function";

		char* res = (char*)(malloc(strlen($2)+1));
		strcpy(res, $2);
		s.arr[1] = res;
		
		stringstream ss;
		ss << $1;
		s.arr[2] = ss.str();
		ss.str("");
		ss << 1;
		s.arr[3] = ss.str();
		ss.str("");
		ss << 0;
		s.arr[4] = ss.str();
		s.ret = $5;

		while (!args.empty()) {
			s.vars.push_back(args.front());
			args.erase(args.begin());
		}

		addToTable(s);
		instructions.push_back(createGoto(0));

	}
	;

Fixme: Lbracket_
	{
		$$ = instructions.size()+1;
	}
	;

Args: Identifier
	{
		if (m_addr < MAX_M_ADDR) {
			Symbol s;
			s.arr[0] = "variable";
			s.arr[1] = $1;
			stringstream ss;
			ss << m_addr;
			s.arr[2] = ss.str();
			s.arr[3] = "1";
			args.push_back($1);
			addToTable(s);
			m_addr++;
		} else {
			yyerror("M_Addr list full. Exiting");
		}

	}
	| Identifier Args
	{

		vector<string> vars;
		if (m_addr < MAX_M_ADDR) {
			Symbol s;
			s.arr[0] = "variable";
			s.arr[1] = $1;
			stringstream ss;
			ss << m_addr;
			s.arr[2] = ss.str();
			s.arr[3] = "1";
			args.push_back($1);
			addToTable(s);
			m_addr++;
		} else {
			yyerror("M_Addr list full. Exiting");
		}
	}
	;
statements:	/* empty */ {
		$$ = instructions.size();
	}
	| statements statement
	{
		$$ = instructions.size();
	}
	;

statement: assignmentstatement
	{
		$$ = $1;
	}
	| readstatement
	{
		$$ = $1;
	}
	| printstatement
	{
		$$ = $1;
	}
	| ifstatement
	{
		$$ = $1;
	}
	| loopstatement
	{
		$$ = $1;
	}
	| whilestatement
	{
		$$ = $1;
	}
	;

assignmentstatement: Lbracket_ Assign_ Identifier AParameter Rbracket_
	{

		int index = findSymbolIndex($3);
		if (index == -1) {
			Symbol s;
			s.arr[0] = "variable";
			s.arr[1] = $3;
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
		index = findSymbolIndex($3);

		int v = $4;
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
	;

Assign_: Assign
	{
		ln = $1;
	}
	;

AParameter: Parameter
	{
		int reg = $1;
		$$ = $1;
	}

Parameter: FunctionCall
	{

		int reg = $1;
		$$ = reg;
		sp.n = 1;
	}
	| Identifier
	{


		sp.fnc = -1;
		int index = findSymbolIndex($1);
		
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
			$$ = reg;
			
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
			$$ = reg;
			sp.n = 1;
		}

	}
	| Number
	{
		
		int reg = findRegister();
		stringstream ss;
		ss << "load R" << reg << " " << sp.n << ";";
		instructions.push_back(ss.str());
		claimRegister(reg);
		$$ = reg;
		sp.n = 1;
		sp.fnc = -1;
	}
	;

PFPFix:
	{
		instructions.push_back(instructions.back());
	}
	;

FunctionCall: FLbracket_ FParams Rbracket_
	{
		int index = $1;

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

		$$ = $2;

		sp.func = findSymbolIndex(sym_table[index].ret);
		sp.fnc = 1;
	}
	| Lbracket_ Function PFPFix PFParam Rbracket_
	{
		string str = $2;
		str = str.substr(0,2);
		if (str == "**") {
			int reg = $4;
			stringstream ss;
			ss << "square R" << reg << ";";
			instructions.push_back(ss.str());
			$$ = reg;
		} else {
			yyerror("Pre-defined functions other than ** require more than 1 param");
		}
		sp.fnc = -1;
	}
	| Lbracket_ Function PFPFix PFParam Hotfix Rbracket_
	{


		string op;

		string t = $2;
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
		ss << op << " R" << $4 << " R" << $5 << ";";
		instructions.push_back(ss.str());
		freeRegister($5);
		$$ = $4;
		sp.fnc = -1;
		
	}
	| PF2 PFParams Rbracket_ {
		string op = instructions.back();
		stringstream ss;
		ss << op << " R" << $1 << " R" << $2 << ";";
		instructions.pop_back();
		instructions.push_back(ss.str());

		freeRegister($2);
		$$ = $1;

		sp.fnc = -1;
		
	}
	;

Hotfix: PFParam
	{
		instructions.pop_back();
		$$ = $1;
	};

PFParams: PFParam
	{
		$$ = $1;
		
	
	}
	| PFParam PFParams
	{
		string op = instructions.at(instructions.size()-1);
		stringstream ss;
		ss << op << " R" << $1 << " R" << $2 << ";";

		instructions.at(instructions.size()-1) = ss.str();
		instructions.push_back(op);
		

		freeRegister($2);
		$$ = $1;
		
	}
	;

PF2: Lbracket_ Function PFPFix PFParam PFParam
	{
		stringstream ss;
		ss << $2[0];
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
		ss << op << " R" << $4 << " R" << $5 << ";";
		instructions.pop_back();
		instructions.push_back(ss.str());
		instructions.push_back(op);
		freeRegister($5);
		$$ = $4;
	}
	;

PFParam: FunctionCall
	{
		string op = instructions.back();
		
		stringstream ss;
		instructions.pop_back();
		instructions.push_back(op);

		$$ = $1;
	}
	| Identifier
	{

		int index = findSymbolIndex($1);
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
			$$ = reg;
			
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
			$$ = reg;
		}
	}
	| Number
	{

		int reg = findRegister();
		stringstream ss;
		ss << "load R" << reg << " " << sp.n << ";";
		string op = instructions.back();
		instructions.back() = ss.str();
		instructions.push_back(op);
		claimRegister(reg);
		$$ = reg;
	}
	;

FLbracket_: Lbracket_ Identifier
	{
		int index = findSymbolIndex($2);
		if (index == -1) {
			yyerror("Cannot call undefined function");
		} else if (sym_table[index].arr[0] != "function") {
			yyerror("Identifier in function call is not a function");
		}
		stringstream ss;
		ss << index;
		instructions.push_back(ss.str());
		
		$$ = index;
	}
	;

FPFix:
	{
		if (fix == -1) {
			int index;
			stringstream ss;
			ss << instructions.back();
			ss >> index;
			$$ = index;
			fix = index;
			instructions.pop_back();
		} else {
			$$ = fix;
		}
	}
	;


FParams:
	FPFix Parameter FParams
	{
		int index = $1;
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

		int reg = $2;
		freeRegister(reg);
		ss << "store R" << reg << " M" << addr << ";";
		instructions.push_back(ss.str());
	}
	| FPFix Parameter {
		int index = $1;
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

		int reg = $2;
		freeRegister(reg);
		ss << "store R" << reg << " M" << addr << ";";
		instructions.push_back(ss.str());
		fix = -1;

	};

/*
	| FPFix Parameter
	{
		string fnc;
		int index = $1;
		stringstream ss;
		ss << index;
		ss >> fnc;

		ss.str("");
		ss.clear();

		if (sym_table[index].vars.size() != 1) {
			cout << sym_table[index].vars.size() << endl;
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

		int reg = $2;
		freeRegister(reg);
		ss << "store R" << reg << " M" << addr << ";";
		instructions.push_back(ss.str());
	}
	;

*/

readstatement:	Lbracket_ Read RID Rbracket_
	{
		stringstream ss;
		ss << "read " << $3 << ";";
		instructions.push_back(ss.str());
	}
	;


RID:	Identifier
	{
		int index = findSymbolIndex($1);
		if (index == -1) {
			Symbol s;
			s.arr[0] = "variable";
			s.arr[1] = $1;
			stringstream ss;
			ss << m_addr;
			s.arr[2] = ss.str(); 
			if (m_addr >= MAX_M_ADDR) {
				yyerror("Too many variables!");
			}
			m_addr++;
			s.arr[3] = "1";
			addToTable(s);
			index = findSymbolIndex($1);
			ss.str("");
			ss << "M" << sym_table[index].arr[2];

			string t = ss.str();
			char* res = (char*)(malloc(t.length()+1));
			strcpy(res, t.c_str());
			$$ = res;
		} else if (sym_table[index].arr[0] == "variable") {
			stringstream ss;
			ss << "M" << sym_table[index].arr[2];

			string t = ss.str();
			char* res = (char*)(malloc(t.length()+1));
			strcpy(res, t.c_str());
			$$ = res;
		} else {
			yyerror("Cannot redefine constant or function!");
		}
	}
	| RID Identifier
	{
		int index = findSymbolIndex($2);
		if (index == -1) {
			Symbol s;
			s.arr[0] = "variable";
			s.arr[1] = $2;
			stringstream ss;
			ss << m_addr;
			s.arr[2] = ss.str(); 
			if (m_addr >= MAX_M_ADDR) {
				yyerror("Too many variables!");
			}
			m_addr++;
			s.arr[3] = "1";
			addToTable(s);
			index = findSymbolIndex($2);
			ss.str("");
			ss << $1 << " M" << sym_table[index].arr[2];
			
			string t = ss.str();
			char* res = (char*)(malloc(t.length()+1));
			strcpy(res, t.c_str());
			$$ = res;

		} else if (sym_table[index].arr[0] == "variable") {

			stringstream ss;
			ss << $1 << " M" << sym_table[index].arr[2];

			string t = ss.str();
			char* res = (char*)(malloc(t.length()+1));
			strcpy(res, t.c_str());
			$$ = res;
		} else {
			yyerror("Cannot redefine constant or function!");
		}

	}
	;
printstatement: Lbracket_ Print PrintParams Rbracket_
	{
		stringstream ss;
		ss << "print " << $3 << ";";
		instructions.push_back(ss.str());
		
	}
	;

PrintParams:	PrintParam
	{
		$$ = $1;
	}
	| PrintParams PrintParam
	{
		stringstream ss;
		ss << $1 << " " << $2;
		string t = ss.str();
		char* res = (char*)(malloc(t.length()+1));
		strcpy(res, t.c_str());
		$$ = res;
	}
	;

PrintParam: Identifier
	{
		int index = findSymbolIndex($1);
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
			$$ = res;
		} else if (sym_table[index].arr[0] == "constant") {
			stringstream ss;

			ss << sym_table[index].arr[3];
			string z = ss.str();
			
			char* res = (char*)(malloc(z.length()+1));
			strcpy(res, z.c_str());
			$$ = res;
		}
	}
	| Sparam
	{
		int s = $1;

		if (s == NUMBER) {
			stringstream ss;
			ss << sp.n;
			string z = ss.str();
			char* res = (char*)(malloc(z.length()+1));
			strcpy(res, z.c_str());
			$$ = res;
		} else if (s == BOOLEAN) {
			string z = "0";
			if (sp.b) {
				z = "1";
			}
			char* res = (char*)(malloc(z.length()+1));
			strcpy(res, z.c_str());
			$$ = res;
		} else if (s == CHAR_STRING) {
			char* res = (char*)(malloc(sp.c.length()+1));
			strcpy(res, sp.c.c_str());
			$$ = res;
		}
	}
	;

ifstatement: Lbracket_ If SExpn Then_ statements Else_ statements Rbracket_
	{

		int v = $3;
		int nr = findRegister();

		int istr = $4;
		stringstream ss;
		ss << "load R" << nr << "M" << v << ";";
		instructions.at(istr) = ss.str();
		ss.str("");
		ss.clear();
		ss << "if R" << v << " " << istr+3 << ";";
		instructions.at(istr+1) = ss.str(); 
		ss.str("");
		ss.clear();
		int t = $6+2;
		instructions.at(istr+2) = createGoto(t);
		ss << "goto " << $7+1 << ";";
		
		int a = $6;
		instructions.at(a) = (ss.str());
	}
	;

SExpn: Expn
	{
		int v = $1;
		freeRegister(v);
		if (m_addr < MAX_M_ADDR) {
			stringstream ss;
			ss << "store R" << v << " M" << m_addr << ";";
			instructions.push_back(ss.str());
			$$ = m_addr;
			m_addr++;
		} else {
			yyerror("Out of memory addresses");
		}
		
	}
	;

Then_: Then {

	$$ = instructions.size();
	instructions.push_back("dummy");
	instructions.push_back("dummy");
	instructions.push_back("dummy");

}

Else_: Else {
	$$ = instructions.size();
	instructions.push_back("dummy");
}

loopstatement: Lbracket_ Loop_ statements Rbracket_
	{
		stringstream ss;
		ss << instructions.at($2);
		int reg;
		ss >> reg;


		stringstream ss1;
		ss1 << "goto " << $3+2 << ";";
		instructions.at($2) = ss1.str();
		ss1.str("");
		ss1 << "goto " << $2 << ";";
		instructions.push_back(ss1.str());
		ss1.str("");
		//ss1 << "mul R1 1;";
		//instructions.push_back(ss1.str());
		freeRegister(reg);
		
	}
	;

Loop_: Loop Identifier
	{
		int reg = findRegister();
		claimRegister(reg);
		int index = findSymbolIndex($2);

		if (sym_table[index].arr[0] == "constant" && sym_table[index].arr[2] == "integer") {
			stringstream ss;
			ss << "load R" << reg << " " << sym_table[index].arr[3] << ";";
			instructions.push_back(ss.str());
			ss.str("");
			ss << "if R" << reg << " " << (instructions.size()+3) << ";";
			instructions.push_back(ss.str());
			$$ = instructions.size();
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
			$$ = instructions.size();
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
	;

whilestatement: Lbracket_ While_ statements Rbracket_
	{

		stringstream ss;
		ss << instructions.at($2);
		int reg;
		ss >> reg;
		ss.str("");
		ss.clear();
		ss << "goto " << $3+2 << ";";
		instructions.at($2) = ss.str();
		ss.str("");
		ss.clear();
		int sz = $2-3;
		ss << "goto " << sz << ";";
		instructions.push_back(ss.str());
		
		freeRegister(reg);
		
	}
	;


While_: While Expn
	{

		stringstream ss;
		int sz = instructions.size()+3;
		ss << "if R" << $2 << " " << sz << ";";
		instructions.push_back(ss.str());

		ss.str("");
		ss.clear();
		ss << $2;
		$$ = instructions.size();
		instructions.push_back(ss.str());


	}
	;

Expn: Lbracket_ CompOp Parameter Parameter Rbracket_
	{
		int reg0 = findRegister();
		claimRegister(reg0);
		int reg1 = $3;
		int reg2 = $4;

		stringstream ss;
		ss << $2 << " R" << reg0 << " R" << reg1 << " R" << reg2 << ";";
		instructions.push_back(ss.str());


		freeRegister(reg2);
		freeRegister(reg1);
		$$ = reg0;
	}
	| Lbracket_ Boolean Rbracket_
	{
		int reg = findRegister();
		claimRegister(reg);

		string z = "0";
		if ($2) {
			z = "1";
		}
		stringstream ss;
		ss << "load R" << reg << " " << z << ";";
		instructions.push_back(ss.str());

		$$ = reg;
	}
	;

CompOp: EQ
	{
		string s = "==";
		char* res = (char*)(malloc(s.length()+1));
		strcpy(res, s.c_str());
		$$ = res;
	}
	| NEQ
	{
		string s = "!=";
		char* res = (char*)(malloc(s.length()+1));
		strcpy(res, s.c_str());
		$$ = res;

	}
	| GTE
	{
		string s = ">=";
		char* res = (char*)(malloc(s.length()+1));
		strcpy(res, s.c_str());
		$$ = res;

	}
	| LTE
	{
		string s = "<=";
		char* res = (char*)(malloc(s.length()+1));
		strcpy(res, s.c_str());
		$$ = res;
	}
	| GT
	{
		string s = ">";
		char* res = (char*)(malloc(s.length()+1));
		strcpy(res, s.c_str());
		$$ = res;
	}
	| LT {
		string s = "<";
		char* res = (char*)(malloc(s.length()+1));
		strcpy(res, s.c_str());
		$$ = res;
	}
	;


	
%%

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

