#ifndef XML_COMMAND_HPP
#define XML_COMMAND_HPP

#include "Node.hpp"

class XMLInvoker;

class XMLCommand {
protected:
    XMLCommand() {}

public:
    virtual void execute(const std::string&) = 0;
};

class ParseFileCommand : public XMLCommand {
private:
    XMLInvoker* invoker;

public:
    ParseFileCommand(XMLInvoker*);
    virtual void execute(const std::string&) override;
};

class SerializeCommand : public XMLCommand {
private:
    XMLInvoker* invoker;

public:
    SerializeCommand(XMLInvoker*);

    virtual void execute(const std::string&) override;
};

class AddAttributeCommand : public XMLCommand {
private:
    XMLInvoker* invoker;

public:
    AddAttributeCommand(XMLInvoker*);

    virtual void execute(const std::string&) override;
};

class IterateToStdoutCommand : public XMLCommand {
private:
    XMLInvoker* invoker;
    void printToStdout(dom::Node*);

public:
    IterateToStdoutCommand(XMLInvoker*);

    virtual void execute(const std::string&) override;
};

#endif // XML_COMMAND_HPP
