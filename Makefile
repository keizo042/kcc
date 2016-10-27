top=.
src=ast.c gen.c kcc.c lex.c parser.c
testdir=./test
opt= -I$(top)
bin=$(top)/bin

.PHONY: all  verbose ready alltest lex parser gen test clean

all: ready lex parser gen
	gcc $(opt) -c main.c 
	gcc $(opt) main.o lex.o parser.o gen.o -o $(bin)/kcc

ready:
	[ -d $(bin) ] || mkdir $(bin)


lex:
	gcc $(opt) -c lex.c

parser:
	gcc $(opt) -c parser.c

gen:
	gcc $(opt) -c gen.c

verbose: all

test:
	
alltest:

clean:
	rm -rf $(bin)
	rm *.o > /dev/null 2>&1
