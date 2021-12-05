#include "Test.hpp"

void testInterpreter(int argc, char** argv) {
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

    // XMLBuilder* builder = new XMLBuilder();
    // XMLDirector director(builder, argv[2]);
    // director.construct();
    // dom::Document* builtDocument = director.getResult();

    // dom::Iterator* it = builtDocument->createIterator();
    // dom::Node* currentNode;

    // XMLInterpreter* interpreter = new XMLInterpreter();

    // for (it->first(); !it->isDone(); it->next()) {

    //     currentNode = it->currentItem();
    //     if (dynamic_cast<dom::Element*>(currentNode)) {
    //         interpreter->interpret(dynamic_cast<dom::Element*>(currentNode));
    //     }
    // }

    // std::cout << "RESULT: " << interpreter->eval() << '\n';

    // delete interpreter;
    // delete builtDocument;
    // delete builder;
    // delete it;
}
