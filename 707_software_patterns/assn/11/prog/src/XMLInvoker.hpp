#ifndef XML_INVOKER_HPP
#define XML_INVOKER_HPP

#include "XMLCommand.hpp"

class XMLInvoker {
private:
    std::vector<XMLCommand*> cmds;
    std::vector<std::string> args;
    dom::Document* document;

public:
    XMLInvoker();
    virtual ~XMLInvoker();

    virtual void addCommand(XMLCommand*, const std::string& = "");
    virtual void setDocument(dom::Document*);
    virtual dom::Document* getDocument();
    virtual void run();
};

#endif // XML_INVOKER_HPP
