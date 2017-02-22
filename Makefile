projroot=$(dirname $0)
.PHONY: all test buildclean testclean

all: ast.c lex.c parser.c gen.c main.c ast.h lex.h parser.h gen.h
	gcc -I. -c ast.c lex.c parser.c gen.c main.c
	gcc -I. *.o -o kcc


test: 
	echo "test"

clean : buildclean testclean
	
buildclean:
	rm -f *.o *.gch  kcc

testclean:
	rm -f *.out 

