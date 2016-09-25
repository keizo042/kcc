#!/usr/bin/env bash
PWD=`dirname $0`
INCLUDE_DIR="$PWD"
TEST_DIR="$PWD/test"
TEST_INCLUDE_DIR=$TEST_DIR
CC="clang -pedantic -Wall -Wno-unused-function"

case $1 in
    "test" )
        for f in $(ls $PWD | grep .c$);
        do
            $CC -c $f
            if [ ! $? -eq 0 ]; then
                echo "fail"
                exit 1;
            fi
        done

        for f in $( ls $TEST_DIR | grep .c$ );
        do
            $CC -g -I$INCLUDE_DIR -I$TEST_INCLUDE_DIR $TEST_DIR/$f  -o $TEST_DIR/${f%.c}.out
        done
        ;;
    "clean")
        rm -rf *.o  ./kcc $TEST_DIR/*.out $TEST_DIR/*.dSYM >> /dev/null 2>&1

        ;;
    * )
        F=""
        for f in $(ls $PWD | grep .c$ | grep -v main.c )
        do
            $CC -I$INCLUDE_DIR -c $f
            if [ ! $? -eq 0 ]; then
                echo "fail"
                exit -1;
            fi
            F="$F ${f%.c}.o"
        done
        echo "build main..."
        $CC -I$INCLUDE_DIR  -c main.c  
        echo "build kcc..."
        $CC -I$INCLUDE_DIR  main.o -o kcc 
        ;;
esac
exit 0;
