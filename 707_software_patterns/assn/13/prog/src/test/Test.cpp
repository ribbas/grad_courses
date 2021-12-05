#include "Test.hpp"
#include <stdio.h>

int main(int argc, char** argv) {

    if (argc < 2) {
        printUsage();
        exit(0);
    }

    switch (argv[1][0]) {
        case 'B':
        case 'b':
            testBuilder(argc, argv);
            break;
        case 'E':
        case 'e':
            testFacade(argc, argv);
            break;
        case 'I':
        case 'i':
            testFacade(argc, argv);
            break;
        case 'T':
        case 't':
            testTokenizer(argc, argv);
            break;
        case 'S':
        case 's':
            testSerializer(argc, argv);
            break;
        case 'V':
        case 'v':
            testValidator(argc, argv);
            break;
    }

    return 0;
}
