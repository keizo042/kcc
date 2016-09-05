#!/usr/bin/env bash
ROOT_DIR=`dirname $0`

case $1 in
    "test")
        gcc -I$ROOT_DIR -I$ROOT_DIR/test -c kcc.c 
        if [ $? -ne 0 ]; then
            exit $?
        fi
        gcc -I$ROOT_DIR -I$ROOT_DIR/test kcc.o test/test1.c -o $ROOT_DIR/test/test1
        ./test/test1
        if [ $? -ne 0 ]; then
            echo "fail"

        fi
        gcc -I$ROOT_DIR -I$ROOT_DIR/test kcc.o test/test2.c -o $ROOT_DIR/test/test2
        ./test/test2
        if [ $? -ne 0 ]; then
            echo "fail"
        fi
        gcc -I$ROOT_DIR -I$ROOT_DIR/test kcc.o test/test3.c -o $ROOT_DIR/test/test3
        ./test/test3
        if [ $? -ne 0 ]; then
            echo "fail"
        fi
    ;;
    "cleanup" | "clean")
        rm *.o  $ROOT_DIR/test/*.o kcc $ROOT_DIR/test/test
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

