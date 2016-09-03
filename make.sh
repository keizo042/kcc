#!/usr/bin/env bash
ROOT_DIR=`dirname $0`

case $1 in
    "test")
        gcc -I $ROOT_DIR -c test/main.c -o test/main.o
        gcc -I $ROOT_DIR  -c kcc.c 
        gcc -I $ROOT_DIR kcc.o test/main.c -o $ROOT_DIR/test/test
        $ROOT_DIR/test/test
    ;;
    "cleanup" | "clean")
        rm *.o  $ROOT_DIR/test/*.o kcc $ROOT_DIR/test/test
    ;;
    *)
        gcc -c kcc.c 
        gcc -c main.c
        gcc kcc.o main.o -o kcc
    ;;

esac

