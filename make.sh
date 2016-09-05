#!/usr/bin/env bash
ROOT_DIR=`dirname $0`

case $1 in
    "test")
        gcc -g -I$ROOT_DIR -I$ROOT_DIR/test -DDEBUG -c kcc.c 
        if [ $? -ne 0 ]; then
            exit $?
        fi
        gcc -g -I$ROOT_DIR -I$ROOT_DIR/test -DDEBUG kcc.o test/test1.c -o $ROOT_DIR/test/test1.out
        ./test/test1.out
        if [ $? -ne 0 ]; then
            echo "fail"

        fi
        gcc -g -I$ROOT_DIR -I$ROOT_DIR/test -DDEBUG kcc.o test/test2.c -o $ROOT_DIR/test/test2.out
        ./test/test2.out
        if [ $? -ne 0 ]; then
            echo "fail"
        fi
        gcc -g -I$ROOT_DIR -I$ROOT_DIR/test -DDEBUG kcc.o test/test3.c -o $ROOT_DIR/test/test3.out
        ./test/test3.out
        if [ $? -ne 0 ]; then
            echo "fail"
        fi
    ;;
    "cleanup" | "clean")
        rm *.o  $ROOT_DIR/test/*.o kcc $ROOT_DIR/test/*.out > /dev/null 2>&1
    ;;
    *)
        echo "gcc -c kcc.c..."
        gcc -I $ROOT_DIR -c kcc.c 
        if [ $? -ne 0 ]; then
            exit $?
        fi
        echo "gcc -c main.c..."
        gcc -I $ROOT_DIR -c main.c
        if [ $? -ne 0 ]; then
            exit $?
        fi
        echo "gcc kcc.o main.o -o kcc..."
        gcc -I $ROOT_DIR kcc.o main.o -o kcc
        if [ $? -ne 0 ]; then
            exit $?
        fi
    ;;

esac

