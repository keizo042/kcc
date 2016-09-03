#!/usr/bin/env bash
ROOT_DIR=`dirname $0`

case $1 in
    "test")
        gcc -I $ROOT_DIR -c test/main.c -o test/main.o
        if [ $? -ne 0 ]; then
            exit $?
        fi
        gcc -I $ROOT_DIR  -c kcc.c 
        if [ $? -ne 0 ]; then
            exit $?
        fi
        gcc -I $ROOT_DIR kcc.o test/main.c -o $ROOT_DIR/test/test
        if [ $? -ne 0 ]; then
            exit $?
        fi
        $ROOT_DIR/test/test
    ;;
    "cleanup" | "clean")
        rm *.o  $ROOT_DIR/test/*.o kcc $ROOT_DIR/test/test
    ;;
    *)
        gcc -c kcc.c 
        if [ $? -ne 0 ]; then
            exit $?
        fi
        gcc -c main.c
        if [ $? -ne 0 ]; then
            exit $?
        fi
        gcc kcc.o main.o -o kcc
        if [ $? -ne 0 ]; then
            exit $?
        fi
    ;;

esac

