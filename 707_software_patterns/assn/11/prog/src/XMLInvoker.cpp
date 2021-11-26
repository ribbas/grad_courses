#include "XMLInvoker.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

XMLInvoker::XMLInvoker() : document(nullptr) {}

XMLInvoker::~XMLInvoker() {}

void XMLInvoker::setDocument(dom::Document* doc) {
    document = doc;
}

dom::Document* XMLInvoker::getDocument() {
    return document;
}

void XMLInvoker::addCommand(XMLCommand* command, const std::string& arg) {
    cmds.push_back(command);
    args.push_back(arg);
}

void XMLInvoker::run() {

    if (cmds.size() == args.size()) {

        for (unsigned int i = 0; i < cmds.size(); i++) {
            std::cout << cmds.at(i) << ' ' << args.at(i) << '\n';
            cmds.at(i)->execute(args.at(i));
        }
    }
}
