CC=g++
CFLAGS=-Wall -w
all: 
	yacc -d FP.yacc
	lex FP.lex
	$(CC) $(CFLAGS) y.tab.c lex.yy.c -lfl -o Parser
clean:
	rm lex.yy.c
	rm y.tab.h
	rm y.tab.c
	rm Parser
