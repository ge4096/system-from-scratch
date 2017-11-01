#!/bin/bash

TMPFILE=$(mktemp /tmp/asm-test.XXXXXX)
SUCCESS=0

test_command () {
    if [ $SUCCESS -eq 0 ]; then
        eval $1 > $TMPFILE
        if [ ! $? -eq 0 ]; then
            cat $TMPFILE
            echo
            echo "======="
            echo " ERROR"
            echo "======="
            echo $1 "failed"
            echo
            SUCCESS=1
        fi
    fi
}

cd $(dirname "$0")/..
make clean > /dev/null

test_command "make ARGCFLAGS=-Werror"
test_command "make test ARGCFLAGS=-Werror"
test_command "./test/asm-test"
test_command "valgrind -q --leak-check=full --error-exitcode=1 ./test/asm-test"

if [ $SUCCESS -eq 0 ]; then
    echo
    echo "========="
    echo " SUCCESS"
    echo "========="
    echo
fi

rm $TMPFILE