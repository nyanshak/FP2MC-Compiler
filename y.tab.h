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
typedef union {
	float num;
	char* char_string;
	bool bval;
	int lineNum;
} YYSTYPE;
extern YYSTYPE yylval;
