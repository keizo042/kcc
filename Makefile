projroot=$(dirname $0)
.PHONY: all test buildclean testclean

all: ast.c lex.c parser.c gen.c main.c ast.h lex.h parser.h gen.h
	gcc -g -I. -c ast.c lex.c parser.c gen.c main.c
	gcc -g -I. *.o -o kcc


test: 
	echo "test"

clean : buildclean testclean
	
buildclean:
	rm -f *.o *.gch  kcc

testclean:
	rm -f *.out 

