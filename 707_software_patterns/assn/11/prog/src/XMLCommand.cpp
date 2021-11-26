#include "XMLCommand.hpp"
#include "XMLDirector.hpp"
#include "XMLInvoker.hpp"
#include "XMLSerializer.hpp"
#include <iostream>

ParseFileCommand::ParseFileCommand(XMLInvoker* invoker_) : invoker(invoker_) {}

void ParseFileCommand::execute(const std::string& args) {

    if (!args.size()) {
        std::cout << "No arguments provided\n";
        return;
    }

    XMLBuilder* builder = new XMLBuilder();
    XMLDirector director(builder, args);
    director.construct();

    invoker->setDocument(director.getResult());
    delete builder;
}

SerializeCommand::SerializeCommand(XMLInvoker* invoker_) : invoker(invoker_) {}

void SerializeCommand::execute(const std::string& args) {

    if (!args.size()) {
        std::cout << "No arguments provided\n";
        return;
    }

    std::fstream* file = nullptr;
    XMLSerializer xmlSerializer(file =
                                    new std::fstream(args, std::ios_base::out));
    xmlSerializer.serializeMinimal(invoker->getDocument());
    delete file;
}

AddAttributeCommand::AddAttributeCommand(XMLInvoker* invoker_)
    : invoker(invoker_) {}

void AddAttributeCommand::execute(const std::string& args) {

    if (!args.size()) {
        std::cout << "No arguments provided\n";
        return;
    }

    dom::Element* child = invoker->getDocument()->createElement("newelement");

    size_t pos = args.find(";");
    dom::Attr* newAttribute =
        invoker->getDocument()->createAttribute(args.substr(0, pos));
    newAttribute->setValue(args.substr(pos + 1));

    child->setAttributeNode(newAttribute);
    invoker->getDocument()->appendChild(child);
}

IterateToStdoutCommand::IterateToStdoutCommand(XMLInvoker* invoker_)
    : invoker(invoker_) {}

void IterateToStdoutCommand::printToStdout(dom::Node* node) {
    if (dynamic_cast<dom::Document*>(node) != 0) {
        std::cout << " (document)";
    } else if (dynamic_cast<dom::Element*>(node) != 0) {
        std::cout << " (element) "
                  << dynamic_cast<dom::Element*>(node)->getTagName();
    } else if (dynamic_cast<dom::Attr*>(node) != 0) {
        std::cout << " (attr) " << dynamic_cast<dom::Attr*>(node)->getName()
                  << ' ' << dynamic_cast<dom::Attr*>(node)->getValue();
    } else if (dynamic_cast<dom::Text*>(node) != 0) {
        std::cout << " (text) " << dynamic_cast<dom::Text*>(node)->getValue();
    }
}

void IterateToStdoutCommand::execute(const std::string&) {

    dom::Iterator* it = invoker->getDocument()->createIterator();
    dom::Node* currentNode;
    for (it->first(); !it->isDone(); it->next()) {

        currentNode = it->currentItem();
        std::cout << currentNode;
        printToStdout(currentNode);
        std::cout << std::endl;
    }

    delete it;
}
