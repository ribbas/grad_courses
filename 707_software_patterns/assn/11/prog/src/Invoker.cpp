#include "Invoker.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

Invoker::Invoker() : document(nullptr) {}

Invoker::~Invoker() {}

void Invoker::setDocument(dom::Document* doc) {
    document = doc;
}

dom::Document* Invoker::getDocument() {
    return document;
}

void Invoker::addCommand(Command* command, const std::string& arg) {
    commands.push_back(command);
    args.push_back(arg);
}

void Invoker::run() {

    if (commands.size() == args.size()) {

        for (unsigned int i = 0; i < commands.size(); i++) {
            std::cout << commands.at(i) << ' ' << args.at(i) << '\n';
            commands.at(i)->execute(args.at(i));
        }
    }
}
