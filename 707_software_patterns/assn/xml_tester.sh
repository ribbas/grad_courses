#!/usr/bin/zsh

TEST1="../../../../Test1.xml"
TEST2="../../../../Test2.xml"
OUT="out.xml"

fname() {
    case "$1" in
        b)
        echo "\nBuilder"
        ;;
        i)
        echo "\nIterator"
        ;;
        t)
        echo "\nTokenizer"
        ;;
        s)
        echo "\nSerializer"
        ;;
        v)
        echo "\nValidator"
        ;;
        *)
        exit 1
        ;;
    esac
}

run() {    
    ./Patterns $1 $2 &> /dev/null || echo $(fname $1) "Failed"
}

run2() {
    ./Patterns $1 $2 ${OUT} &> /dev/null || echo $(fname $1) "Failed"
    if (( # == 2 )); then
        cmp --silent $2 ${OUT} || echo "Different output"
    elif (( # == 3 )); then
        cmp --silent $3 ${OUT} || echo "Different output"
    fi
}

run2 b ${TEST1}

run i ${TEST1}

run t ${TEST1}
run t ${TEST2}

run2 s ${TEST1} ${TEST2}

run v ${TEST1}
