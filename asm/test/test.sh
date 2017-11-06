#!/bin/bash

TMPFILE=$(mktemp /tmp/sfsasm-test.XXXXXX)
SUCCESS=0

test_command () {
    if [ $SUCCESS -eq 0 ]; then
        echo "Running" $1
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

for DEP in "diff" "make" "valgrind"; do
    command -v $DEP > /dev/null
    if [ ! $? -eq 0 ]; then
        echo "Could not locate dependency" $DEP
        SUCCESS=1
    fi
done

cd $(dirname "$0")/..
make clean > /dev/null

test_command "make ARGCFLAGS=-Werror"
test_command "make test ARGCFLAGS=-Werror"
test_command "./test/sfsasm-test"
test_command "valgrind -q --leak-check=full --error-exitcode=1 \
./test/sfsasm-test"

rm -f ./test/test_output.s

test_command "./bin/sfsasm ./test/test_input.asm ./test/test_output.s"
test_command "valgrind -q --leak-check=full --error-exitcode=1 ./bin/sfsasm \
./test/test_input.asm ./test/test_output.s"
test_command "diff <(hexdump -C ./test/test_output.s) <(hexdump -C \
./test/test_expected_output.s)"

if [ $SUCCESS -eq 0 ]; then
    echo
    echo "========="
    echo " SUCCESS"
    echo "========="
    echo
fi

rm $TMPFILE