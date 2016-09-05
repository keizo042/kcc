#!/usr/bin/env bash
ROOT_DIR=`dirname $0`
TEST_DIR=$ROOT_DIR/test

case $1 in
    "test")
        gcc -g -I$ROOT_DIR -I$TEST_DIR   -c kcc.c 
        if [ $? -ne 0 ]; then
            exit $?
        fi
        gcc -g -I$ROOT_DIR -I$TEST_DIR   kcc.o $TEST_DIR/test1.c -o $TEST_DIR/test1.out
        $TEST_DIR/test1.out
        if [ $? -ne 0 ]; then
            echo "fail"

        fi
        gcc -g -I$ROOT_DIR -I$TEST_DIR   kcc.o $TEST_DIR/test2.c -o $TEST_DIR/test2.out
        $TEST_DIR/test2.out
        if [ $? -ne 0 ]; then
            echo "fail"
        fi
        gcc -g -I$ROOT_DIR -I$TEST_DIR   kcc.o $TEST_DIR/test3.c -o $TEST_DIR/test3.out
        $TEST_DIR/test3.out
        if [ $? -ne 0 ]; then
            echo "fail"
        fi
        gcc -g -I$ROOT_DIR -I$TEST_DIR   kcc.o $TEST_DIR/test_lex_digit.c -o $TEST_DIR/test_lex_digit.out
        $TEST_DIR/test_lex_digit.out
        if [ $? -ne 0 ]; then
            echo "fail"
        fi
        gcc -g -I$ROOT_DIR -I$TEST_DIR   kcc.o $TEST_DIR/test_lex_string.c -o $TEST_DIR/test_lex_string.out
        $ROOT_DIR/test/test_lex_string.out
        if [ $? -ne 0 ]; then
            echo "fail"
        fi
        gcc -g -I$ROOT_DIR -I$TEST_DIR   kcc.o $TEST_DIR/test_lex_skip_comment.c -o $TEST_DIR/test_lex_skip_comment.out
        $TEST_DIR/test_lex_skip_comment.out
        if [ $? -ne 0 ]; then
            echo "fail"
        fi
        gcc -g -I$ROOT_DIR -I$TEST_DIR   kcc.o $TEST_DIR/test_lex_skip_until.c -o $TEST_DIR/test_lex_skip_until.out
        $TEST_DIR/test_lex_skip_until.out
        if [ $? -ne 0 ]; then
            echo "fail"
        fi

    ;;
    "cleanup" | "clean")
        rm $ROOT_DIR/*.o  $TEST_DIR/*.o kcc $TEST_DIR/*.out > /dev/null 2>&1
    ;;
    *)
        echo "gcc -c kcc.c..."
        gcc -I $ROOT_DIR   -c kcc.c 
        if [ $? -ne 0 ]; then
            exit $?
        fi
        echo "gcc -c main.c..."
        gcc -I $ROOT_DIR   -c main.c
        if [ $? -ne 0 ]; then
            exit $?
        fi
        echo "gcc kcc.o main.o -o kcc..."
        gcc -I $ROOT_DIR kcc.o main.o   -o kcc
        if [ $? -ne 0 ]; then
            exit $?
        fi
    ;;

esac

