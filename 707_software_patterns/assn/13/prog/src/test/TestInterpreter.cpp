#include "Test.hpp"

void testInterpreter(int argc, char** argv) {
    if (argc < 2) {
        printUsage();
        exit(0);
    }

    XMLBuilder* builder = new XMLBuilder();
    XMLDirector director(builder, argv[2]);
    director.construct();
    dom::Document* builtDocument = director.getResult();

    dom::Iterator* it = builtDocument->createIterator();
    dom::Node* currentNode;

    XMLInterpreter* interpreter = new XMLInterpreter();

    for (it->first(); !it->isDone(); it->next()) {

        currentNode = it->currentItem();
        if (dynamic_cast<dom::Element*>(currentNode)) {
            interpreter->interpret(dynamic_cast<dom::Element*>(currentNode));
        }
    }

    std::cout << "RESULT: " << interpreter->eval() << '\n';

    delete interpreter;
    delete builtDocument;
    delete builder;
    delete it;
}
