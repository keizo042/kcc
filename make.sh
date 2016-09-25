#!/usr/bin/env bash
PWD=`dirname $0`
INCLUDE_DIR=""
INCLUDE_DIR="$PWD"
TEST_DIR="$PWD/test"
TEST_FILES=" "
TEST_INCLUDE_DIR=$TEST_DIR
CC="clang -std=c99 -std=gnu99"

case $1 in
    "test" )
        for f in $(ls $PWD | grep .c$)
        do
            $CC -g -I$INCLUDE_DIR -c $f
            if [ ! $? -eq 0 ]; then
                echo "fail"
                exit -1;
            fi
        done

        for f in $( ls $TEST_DIR | grep .c$ )
        do
            $CC -g -I$INCLUDE_DIR -I$TEST_INCLUDE_DIR "$TEST_DIR/$f"  -o $TEST_DIR/${f%.c}.out
        done
        ;;
    "clean")
        rm -rf *.o  ./kcc $TEST_DIR/*.out $TEST_DIR/*.dSYM >> /dev/null 2>&1

        ;;
    * )
        F=""
        for f in $(ls $PWD | grep .c$ | grep -v main.c )
        do
            $CC -c -I$INCLUDE_DIR $f
            if [ ! $? -eq 0 ]; then
                echo "fail"
                exit -1;
            fi
            F="$F ${f%.c}.o"
        done
        $CC -I"$INCLUDE_DIR"  -c main.c 
        echo "build kcc..."
        $CC -I"$INCLUDE_DIR"  main.o -o kcc 
        ;;
esac
