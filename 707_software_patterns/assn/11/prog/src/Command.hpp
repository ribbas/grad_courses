#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "Node.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Invoker;

class Command {
protected:
    Command() {}

public:
    virtual ~Command() {}
    virtual void execute() = 0;
};

class ParseFileCommand : public Command {
private:
    std::string fileName;
    dom::Node* rootNode;
    Invoker* state;

public:
    virtual void execute() override;
    ParseFileCommand(const std::string fileName_) : fileName(fileName_) {}
};

class SerializeCommand : public Command {
private:
    dom::Node* node;
    std::fstream* file;
    Invoker* state;

public:
    SerializeCommand(const std::string& fileName)
        : file(new std::fstream(fileName.c_str(), std::ios_base::out)) {}

    ~SerializeCommand() {
        if (file) {
            delete file;
        }
    }
    virtual void execute() override;
};

class AddAttributeCommand : public Command {
private:
    dom::Element* node;
    std::string attrName;
    std::string attrValue;
    Invoker* state;

public:
    AddAttributeCommand(dom::Element* node_, const std::string& attrName_,
                        const std::string& attrValue_)
        : node(node_), attrName(attrName_), attrValue(attrValue_) {}

    virtual void execute() override;
};

#endif // COMMAND_HPP
