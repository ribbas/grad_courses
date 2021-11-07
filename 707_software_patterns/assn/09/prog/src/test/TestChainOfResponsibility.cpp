#include "Test.hpp"

void testChainOfResponsibility(int argc, char** argv) {

    //
    // <xml version="1.0" encoding="UTF-8"?>
    // <handlers>
    // <handler message="type1">
    //     <handler message="type2"/>
    //     <handler message="type2"/>
    // </handler>
    // </handlers>
    //
    if (argc < 2) {
        printUsage();
        exit(0);
    }

    XMLBuilder* builder = new XMLBuilder();
    XMLDirector director(builder, argv[2]);
    director.construct();
    dom::Document* builtDocument = director.getResult();

    //
    // Create an iterator from the document object
    //
    dom::Iterator* it = builtDocument->createIterator();
    dom::Node* currentNode;
    dom::Event* events[3] = {new dom::Event("type1"), new dom::Event("type2"),
                             new dom::Event("type3")};

    for (int i = 0; i < 3; i++) {

        std::cout << "Sending request: " << events[i]->message << '\n';

        for (it->first(); !it->isDone(); it->next()) {

            currentNode = it->currentItem();

            if (dynamic_cast<dom::Element*>(currentNode)) {
                if (dynamic_cast<dom::Element*>(currentNode)
                        ->handleEvent(events[i])) {
                    break;
                }
            }
        }
    }

    // delete Document and tree.
    for (int i = 0; i < 3; i++) {
        delete events[i];
    }
    delete builtDocument;
    delete builder;
    delete it;
}
