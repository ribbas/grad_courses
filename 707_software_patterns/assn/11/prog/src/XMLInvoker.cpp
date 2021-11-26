#include "XMLInvoker.hpp"

XMLInvoker::XMLInvoker() : document(nullptr) {}

XMLInvoker::~XMLInvoker() {

    while (cmds.size()) {
        cmds.pop();
    }

    while (args.size()) {
        args.pop();
    }
}

void XMLInvoker::setDocument(dom::Document* document_) {
    document = document_;
}

dom::Document* XMLInvoker::getDocument() {
    return document;
}

void XMLInvoker::addCommand(XMLCommand* cmd, const std::string& arg) {
    cmds.push(cmd);
    args.push(arg);
}

void XMLInvoker::run() {

    if (cmds.size() == args.size()) {

        while (cmds.size()) {
            cmds.front()->execute(args.front());
            cmds.pop();
            args.pop();
        }
    }
}
