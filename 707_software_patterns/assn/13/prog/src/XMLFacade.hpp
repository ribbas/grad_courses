#ifndef XML_FACADE_HPP
#define XML_FACADE_HPP

#include "Node.hpp"

class XMLFacade {
private:
    dom::Document* document;
    void printToStdout(dom::Node*);

public:
    XMLFacade();
    ~XMLFacade();
    void setDocument(dom::Document*);
    void serialize(const std::string&, bool);
    void parse(const std::string&);
    void tokenize(const std::string&);
    void iterateToStdout();
    void interpret();
};

#endif