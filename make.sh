#!/usr/bin/env bash
PWD=`dirname $0`
INCLUDE_DIR=""
FILES="kcc lex parse ast"
INCLUDE_DIR=""
TEST_FILES=" "
TEST_INCLUDE_DIR="$PWD/test"
CC="gcc -std=c99"

case $1 in
    "test" )
        for f in $FILES 
        do
            $CC -g -c "$f.c"
            if [ ! $? -eq 0 ]; then
                echo "fail"
                exit -1;
            fi
        done
        ;;
    "clean")
        rm *.o  ./kcc >> /dev/null 2>&1

        ;;
    * )
        F=""
        for f in $FILES 
        do
            $CC -c "$f.c"
            if [ ! $? -eq 0 ]; then
                echo "fail"
                exit -1;
            fi
            F="$F $f.o"
        done
        $CC -c main.c
        echo "build kcc..."
        $CC -I"$INCLUDE_DIR" $F main.o -o kcc 
        ;;
esac
