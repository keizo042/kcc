
.PHONY: all test buildclean testclean

all: ast.c ast.h lex.c lex.h parser.c parser.h gen.c gen.h main.c 
	gcc -c ast.c ast.h lex.c lex.h parser.c parser.h gen.c gen.h main.c 
	gcc *.o -o kcc


test: 

clean : buildclean testclean
	
buildclean:
	rm -f *.o *.gch  kcc

testclean:
	rm -f *.out 

