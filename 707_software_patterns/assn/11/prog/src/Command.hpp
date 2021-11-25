#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "Node.hpp"
#include "XMLBuilder.hpp"
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
    virtual void execute(const std::string&) = 0;
};

class ParseFileCommand : public Command {
private:
    Invoker* state;
    XMLBuilder* builder;

public:
    ParseFileCommand(Invoker* invoker)
        : state(invoker), builder(new XMLBuilder()) {}
    virtual void execute(const std::string&) override;

    ~ParseFileCommand() {
        if (builder) {
            delete builder;
        }
    }
};

class SerializeCommand : public Command {
private:
    Invoker* state;
    std::fstream* file;

public:
    SerializeCommand(Invoker* invoker) : state(invoker) {}

    ~SerializeCommand() {
        if (file) {
            delete file;
        }
    }
    virtual void execute(const std::string&) override;
};

class AddAttributeCommand : public Command {
private:
    Invoker* state;

public:
    AddAttributeCommand(Invoker* invoker) : state(invoker) {}

    virtual void execute(const std::string&) override;
};

#endif // COMMAND_HPP
