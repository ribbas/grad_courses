#ifndef XML_DIRECTOR_HPP
#define XML_DIRECTOR_HPP

#include "XMLBuilder.hpp"
#include "XMLTokenizer.hpp"

class XMLDirector {
private:
    XMLBuilder* factory;
    XMLTokenizer tokenizer;

    struct State {
        virtual ~State() {}
        virtual State* process(XMLTokenizer::XMLToken*, XMLBuilder*, bool&) = 0;
    };

    // struct InsideTag : public State {
    //     virtual State* process(dom::Element*, XMLTokenizer::XMLToken*,
    //                            XMLTokenizer::XMLToken::TokenTypes,
    //                            XMLBuilder*);
    // };

    struct InsideAttrName : public State {
        virtual State* process(XMLTokenizer::XMLToken*, XMLBuilder*, bool&);
    };

    // struct InsideAttrValue : public State {
    //     virtual State* process(dom::Element*, XMLTokenizer::XMLToken*,
    //                            XMLTokenizer::XMLToken::TokenTypes,
    //                            XMLBuilder*);
    // };

    struct TagCloseStart : public State {
        virtual State* process(XMLTokenizer::XMLToken*, XMLBuilder*, bool&);
    };

    struct TagCloseEnd : public State {
        virtual State* process(XMLTokenizer::XMLToken*, XMLBuilder*, bool&);
    };

    // struct InNullTag : public State {
    //     virtual State* process(dom::Element*, XMLTokenizer::XMLToken*,
    //                            XMLTokenizer::XMLToken::TokenTypes,
    //                            XMLBuilder*);
    // };

    // struct InElementValue : public State {
    //     virtual State* process(dom::Element*, XMLTokenizer::XMLToken*,
    //                            XMLTokenizer::XMLToken::TokenTypes,
    //                            XMLBuilder*);
    // };

    // struct End : public State {
    //     virtual State* process(dom::Element*, XMLTokenizer::XMLToken*,
    //                            XMLTokenizer::XMLToken::TokenTypes,
    //                            XMLBuilder*);
    // };

    State* currentState;

public:
    XMLDirector(XMLBuilder*, std::string);

    void construct();
    dom::Document* getResult();
};

#endif // XML_DIRECTOR_HPP
