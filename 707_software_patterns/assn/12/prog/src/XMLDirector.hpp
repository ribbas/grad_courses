#ifndef XML_DIRECTOR_HPP
#define XML_DIRECTOR_HPP

#include "XMLBuilder.hpp"
#include "XMLTokenizer.hpp"

class XMLDirector {
private:
    XMLBuilder* factory;
    XMLTokenizer tokenizer;

    struct State {
        virtual ~State();
        virtual void process(XMLTokenizer::XMLToken*, XMLBuilder*) = 0;
    };

    struct InsideAttr : public State {
        virtual void process(XMLTokenizer::XMLToken*, XMLBuilder*);
    };

    struct InsideElement : public State {
        virtual void process(XMLTokenizer::XMLToken*, XMLBuilder*);
    };

    struct AddText : public State {
        virtual void process(XMLTokenizer::XMLToken*, XMLBuilder*);
    };

    struct ParseTag : public State {
        virtual void process(XMLTokenizer::XMLToken*, XMLBuilder*);
    };

    struct InNullTag : public State {
        virtual void process(XMLTokenizer::XMLToken*, XMLBuilder*);
    };

    struct NoOp : public State {
        virtual void process(XMLTokenizer::XMLToken*, XMLBuilder*);
    };

    static bool lastTagState;
    static State* currentState;

public:
    XMLDirector(XMLBuilder*, std::string);

    void construct();
    dom::Document* getResult();
};

#endif // XML_DIRECTOR_HPP
