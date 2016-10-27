#!/usr/bin/env bash
PWD=`dirname $0`
INCLUDE_DIR="$PWD"
TEST_DIR="$PWD/test"
TEST_INCLUDE_DIR=$TEST_DIR
CC="clang -pedantic -Wall -Wno-unused-function"

rm -rf *.o  ./kcc $TEST_DIR/*.out $TEST_DIR/*.dSYM >> /dev/null 2>&1
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
    $CC -g  -I$INCLUDE_DIR -I$TEST_INCLUDE_DIR $TEST_DIR/$f  -c -o $TEST_DIR/${f%.c}.o
    $CC -g  -I$INCLUDE_DIR -I$TEST_INCLUDE_DIR $(ls $PWD | grep .o$ | grep -v main) $TEST_DIR/${f%.c}.o -o $TEST_DIR/${f%.c}.out
done
for obj in $( ls $TEST_DIR | grep .out$ );
do
    printf "run %s......\n"  $obj
    $TEST_DIR/$obj
done
