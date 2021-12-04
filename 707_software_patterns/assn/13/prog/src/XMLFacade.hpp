#ifndef XML_FACADE_HPP
#define XML_FACADE_HPP

#include "Node.hpp"

class XMLFacade {
private:
    static dom::Document* document;
    static void printToStdout(dom::Node*);

public:
    static void setDocument(dom::Document*);
    static void serialize(const std::string&, bool);
    static void parse(const std::string&);
    static void tokenize(const std::string&);
    static void iterateToStdout();
};

#endif