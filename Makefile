top=.
CC=gcc
src=ast.c gen.c kcc.c lex.c parser.c
testdir=./test
opt= -I$(top) -Wall -Wno-unused-function -g
bin=$(top)/bin

.PHONY: all  verbose ready alltest lex parser gen test clean

all: ready lex parser gen
	$(CC) $(opt) -c main.c 
	$(CC) $(opt) main.o lex.o parser.o gen.o -o $(bin)/kcc

ready:
	[ -d $(bin) ] || mkdir $(bin)


lex: lex.c
	$(CC) $(opt) -c lex.c

parser: parser.c
	$(CC) $(opt) -c parser.c

gen: gen.c
	$(CC) $(opt) -c gen.c

verbose: all

test: 
	

	
alltest:

clean:
	rm -rf $(bin)
	rm *.o test/*.o test/*.out > /dev/null 2>&1 || exit 0
