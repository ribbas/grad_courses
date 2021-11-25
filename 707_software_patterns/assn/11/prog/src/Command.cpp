#include "Command.hpp"
#include "Invoker.hpp"
#include "Node.hpp"
#include "XMLDirector.hpp"
#include "XMLSerializer.hpp"
#include <iostream>

void ParseFileCommand::execute(const std::string& args) {

    if (!args.size()) {
        std::cout << "No\n";
        return;
    }

    XMLDirector director(builder, args);
    director.construct();

    state->setDocument(director.getResult());
}

void SerializeCommand::execute(const std::string& args) {

    if (!args.size()) {
        std::cout << "No\n";
        return;
    }

    file = new std::fstream(args.c_str(), std::ios_base::out);
    XMLSerializer xmlSerializer(file);
    xmlSerializer.serializePretty(state->getDocument());
}

void AddAttributeCommand::execute(const std::string& args) {

    std::cout << args << '\n';
    if (!args.size()) {
        std::cout << "No\n";
        return;
    }

    size_t pos = args.find(";");
    std::cout << args.substr(0, pos) << ' ' << args.substr(pos + 1) << '\n';

    dynamic_cast<dom::Element*>(state->getDocument())
        ->setAttribute(args.substr(0, pos), args.substr(pos));
}
