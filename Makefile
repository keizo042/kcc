projroot=$(dirname $0)

# main
.PHONY: all buildmain linkmain build buildclean 

# test
.PHONY: test testmain linktest testclean testbuild testexec


all : buildmain

buildmain: build linkmain

linkmain:
	gcc -g -I. main.o ast.o lex.o parser.o gen.o -o kcc


build: ast.c lex.c parser.c gen.c main.c ast.h lex.h parser.h gen.h
	gcc -g -I. -c ast.c lex.c parser.c gen.c main.c


test: testbuild testexec

testbuild: build linktest testmain

linktest: 
	gcc -g -I. -c lex.c lex_test.c
	gcc -g -I. lex.o lex_test.o -o lex_test.out
	gcc -g -I. -c parser.c parser_test.c
	gcc -g -I. lex.o parser.o parser_test.o -o parser_test.out
	gcc -g -I. -c ast.c gen_test.c
	gcc -g -I. gen.o ast.o gen_test.o -o gen_test.out

testmain:
	./lex_test.out
	./parser_test.out
	./gen_test.out
	

	

clean : buildclean testclean
	
buildclean:
	rm -f *.o *.gch  kcc

testclean:
	rm -f *.out 

