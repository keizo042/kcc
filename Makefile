top=.
CC=gcc
src=ast.c gen.c kcc.c lex.c parser.c
testdir=./test
opt= -I$(top)
bin=$(top)/bin

.PHONY: all  verbose ready alltest lex parser gen test clean

all: ready lex parser gen
	$(CC) $(opt) -c main.c 
	$(CC) $(opt) main.o lex.o parser.o gen.o -o $(bin)/kcc

ready:
	[ -d $(bin) ] || mkdir $(bin)


lex:
	$(CC) $(opt) -c lex.c

parser:
	$(CC) $(opt) -c parser.c

gen:
	$(CC) $(opt) -c gen.c

verbose: all

test: 
	./test.sh
	

	
alltest:

clean:
	rm -rf $(bin)
	rm *.o test/*.o test/*.out > /dev/null 2>&1
