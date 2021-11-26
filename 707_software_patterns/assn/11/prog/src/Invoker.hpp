#ifndef INVOKER_HPP
#define INVOKER_HPP

#include "Command.hpp"

class Invoker {
private:
    std::vector<Command*> cmds;
    std::vector<std::string> args;
    dom::Document* document;

public:
    Invoker();
    virtual ~Invoker();

    virtual void addCommand(Command*, const std::string&);
    virtual void setDocument(dom::Document*);
    virtual dom::Document* getDocument();
    virtual void run();
};

#endif // INVOKER_HPP
