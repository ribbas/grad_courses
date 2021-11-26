#ifndef XML_COMMAND_HPP
#define XML_COMMAND_HPP

#include "Node.hpp"
#include "XMLBuilder.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class XMLInvoker;

class XMLCommand {
protected:
    XMLCommand() {}

public:
    virtual ~XMLCommand() {}
    virtual void execute(const std::string&) = 0;
};

class ParseFileCommand : public XMLCommand {
private:
    XMLInvoker* state;

public:
    ParseFileCommand(XMLInvoker* invoker) : state(invoker) {}
    virtual void execute(const std::string&) override;
};

class SerializeCommand : public XMLCommand {
private:
    XMLInvoker* state;

public:
    SerializeCommand(XMLInvoker* invoker) : state(invoker) {}

    virtual void execute(const std::string&) override;
};

class AddAttributeCommand : public XMLCommand {
private:
    XMLInvoker* state;

public:
    AddAttributeCommand(XMLInvoker* invoker) : state(invoker) {}

    virtual void execute(const std::string&) override;
};

class IterateToStdoutCommand : public XMLCommand {
private:
    XMLInvoker* state;

public:
    IterateToStdoutCommand(XMLInvoker* invoker) : state(invoker) {}

    virtual void execute(const std::string&) override;
};

#endif // XML_COMMAND_HPP
