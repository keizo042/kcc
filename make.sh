#!/usr/bin/env bash 
ROOT_DIR=`dirname $0`
TEST_DIR=$ROOT_DIR/test

MAIN_FILE="kcc main"


case $1 in
    "test")
    TEST_FILE="test1 test2 test3 test_lex_digit test_lex_string test_lex_skip_comment test_lex_skip_until test_lex_token test_lex_skip_brank"

        gcc -g -I$ROOT_DIR -I$TEST_DIR   -c kcc.c 

        for f in $TEST_FILE; do
            gcc -g -I$ROOT_DIR -I$TEST_DIR  kcc.o $TEST_DIR/$f.c -o $TEST_DIR/$f.out
            $TEST_DIR/$f.out
        done

    ;;
    "cleanup" | "clean")
        rm $ROOT_DIR/*.o  $TEST_DIR/*.o kcc $TEST_DIR/*.out $TEST_DIR/*.dSYM > /dev/null 2>&1
    ;;
    *)
        for f in $MAIN_FILE; do
        printf "gcc -c %s.c...\n" $f
        gcc -I $ROOT_DIR   -c $f.c 
        if [ $? -ne 0 ]; then
            exit $?
        fi
        done

        OBJS=""
        for f in $MAIN_FILE; do
        OBJS="$OBJ $f.o"
        done
        printf "gcc %s -o kcc...\n" $OBJS
        gcc -I $ROOT_DIR $OBJS -o kcc
        if [ $? -ne 0 ]; then
            exit $?
        fi
    ;;

esac

