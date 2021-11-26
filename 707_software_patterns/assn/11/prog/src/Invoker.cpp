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
    cmds.push_back(command);
    args.push_back(arg);
}

void Invoker::run() {

    if (cmds.size() == args.size()) {

        for (unsigned int i = 0; i < cmds.size(); i++) {
            std::cout << cmds.at(i) << ' ' << args.at(i) << '\n';
            cmds.at(i)->execute(args.at(i));
        }
    }
}
