#include "Test.hpp"

void testFacade(int argc, char** argv) {
    if (argc < 4) {
        printUsage();
        exit(0);
    }

    XMLFacade* xmlApp = new XMLFacade;

    xmlApp->parse(argv[2]);
    xmlApp->serialize(argv[3], false);
    xmlApp->tokenize(argv[2]);
    xmlApp->iterateToStdout();
    xmlApp->interpret();

    delete xmlApp;
}
