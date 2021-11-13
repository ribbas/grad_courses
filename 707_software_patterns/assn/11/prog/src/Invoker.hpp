#ifndef INVOKER_HPP
#define INVOKER_HPP

#include "Command.hpp"

class Invoker {
private:
    std::vector<Command*> commands;
    bool running;
    dom::Document* document;

    virtual void split(const std::string& input,
                       std::vector<std::string>& output);

public:
    Invoker() : running(true), document(nullptr) {}
    virtual ~Invoker() {}

    virtual void addCommand(Command* command) {
        commands.push_back(command);
    }

    virtual void run();
    virtual void setDocument(dom::Document* d) {
        document = d;
    }
    virtual dom::Document* getDocument() {
        return document;
    }
    virtual void prompt();
    virtual void invoke(const std::string& input);
};

#endif // INVOKER_HPP