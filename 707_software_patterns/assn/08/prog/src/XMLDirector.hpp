#ifndef XML_DIRECTOR_HPP
#define XML_DIRECTOR_HPP

#include "XMLBuilder.hpp"
#include "XMLTokenizer.hpp"

class XMLDirector {
private:
    XMLBuilder* factory;
    XMLTokenizer tokenizer;

public:
    XMLDirector(XMLBuilder*, std::string);

    void construct();
    dom::Document* getResult();
};

#endif // XML_DIRECTOR_HPP
