#ifndef XML_DIRECTOR_H
#define XML_DIRECTOR_H

#include "XMLBuilder.hpp"
#include "XMLTokenizer.hpp"

class XMLDirector {
private:
    XMLBuilder* factory;
    XMLTokenizer tokenizer;

public:
    XMLDirector(XMLBuilder* builder, std::string fileName)
        : factory(builder), tokenizer(fileName) {}

    void construct();

    dom::Document* getResult() {
        return factory->getDocument();
    }
};

#endif
