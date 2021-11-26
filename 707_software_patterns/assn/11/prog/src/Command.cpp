#include "Command.hpp"
#include "Invoker.hpp"
#include "Node.hpp"
#include "XMLDirector.hpp"
#include "XMLSerializer.hpp"
#include <iostream>

void ParseFileCommand::execute(const std::string& args) {

    if (!args.size()) {
        std::cout << "No arguments provided\n";
        return;
    }

    XMLDirector director(builder, args);
    director.construct();

    state->setDocument(director.getResult());
}

void SerializeCommand::execute(const std::string& args) {

    if (!args.size()) {
        std::cout << "No arguments provided\n";
        return;
    }

    std::fstream* file = nullptr;
    XMLSerializer xmlSerializer(file =
                                    new std::fstream(args, std::ios_base::out));
    xmlSerializer.serializePretty(state->getDocument());
    delete file;
}

void AddAttributeCommand::execute(const std::string& args) {

    if (!args.size()) {
        std::cout << "No arguments provided\n";
        return;
    }

    size_t pos = args.find(";");
    std::cout << "1:" << args.substr(0, pos) << ":2:" << args.substr(pos + 1)
              << '\n';

    dom::Element* child = state->getDocument()->createElement("newelement");

    dom::Attr* newAttribute =
        state->getDocument()->createAttribute(args.substr(0, pos));
    newAttribute->setValue(args.substr(pos + 1));
    child->setAttributeNode(newAttribute);
    state->getDocument()->appendChild(child);
}

void IterateToStdoutCommand::execute(const std::string&) {

    dom::Iterator* it = state->getDocument()->createIterator();
    dom::Node* currentNode;
    for (it->first(); !it->isDone(); it->next()) {

        currentNode = it->currentItem();

        if (dynamic_cast<dom::Document*>(currentNode) != 0) {
            std::cout << currentNode << ' ' << currentNode->getNodeName()
                      << std::endl;
        } else if (dynamic_cast<dom::Element*>(currentNode) != 0) {
            std::cout << currentNode << ' ' << currentNode->getNodeName()
                      << std::endl;
        } else if (dynamic_cast<dom::Attr*>(currentNode) != 0) {
            std::cout << currentNode << ' ' << currentNode->getNodeName()
                      << std::endl;
        } else if (dynamic_cast<dom::Text*>(currentNode) != 0) {
            std::cout << currentNode << ' ' << currentNode->getNodeName()
                      << std::endl;
        }
    }

    delete it;
}
