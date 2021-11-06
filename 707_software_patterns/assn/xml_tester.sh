#!/usr/bin/zsh

TEST1="../../../../Test1.xml"
TEST2="../../../../Test2.xml"
OUT="out.xml"

fname() {
    case "$1" in
        b)
        echo "Builder"
        ;;
        c)
        echo "Chain of Responsibility"
        ;;
        i)
        echo "Iterator"
        ;;
        t)
        echo "Tokenizer"
        ;;
        s)
        echo "Serializer"
        ;;
        v)
        echo "Validator"
        ;;
        *)
        exit 1
        ;;
    esac
}

run() {    
    ./Patterns $1 $2 > /dev/null 2>&1 || echo "$(fname $1) failed"
}

run2() {
    ./Patterns $1 $2 ${OUT} > /dev/null 2>&1 || echo "$(fname $1) failed"
    if (( # == 2 )); then
        cmp --silent $2 ${OUT} || echo "$(fname $1) different output"
    elif (( # == 3 )); then
        cmp --silent $3 ${OUT} || echo "$(fname $1) different output"
    fi
}

# builder
run2 b ${TEST1}

# chain of responsibility
run c ${TEST1}

# iterator
run i ${TEST1}

# tokenizer
run t ${TEST1}
run t ${TEST2}

# serializer
run2 s ${TEST1} ${TEST2}

# validator
run v ${TEST1}

# clean up output files
rm ${OUT}
