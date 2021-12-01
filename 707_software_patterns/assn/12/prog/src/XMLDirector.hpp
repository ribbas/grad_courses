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
        virtual State* process(State*, XMLTokenizer::XMLToken*,
                               XMLBuilder*) = 0;
    };

    struct InsideAttr : public State {
        virtual State* process(State*, XMLTokenizer::XMLToken*, XMLBuilder*);
    };

    struct InsideElement : public State {
        virtual State* process(State*, XMLTokenizer::XMLToken*, XMLBuilder*);
    };

    struct AddText : public State {
        virtual State* process(State*, XMLTokenizer::XMLToken*, XMLBuilder*);
    };

    struct TagCloseStart : public State {
        virtual State* process(State*, XMLTokenizer::XMLToken*, XMLBuilder*);
    };

    struct TagCloseEnd : public State {
        virtual State* process(State*, XMLTokenizer::XMLToken*, XMLBuilder*);
    };

    struct InNullTagEnd : public State {
        virtual State* process(State*, XMLTokenizer::XMLToken*, XMLBuilder*);
    };

    struct NoOp : public State {
        virtual State* process(State*, XMLTokenizer::XMLToken*, XMLBuilder*);
    };

    State* currentState;

public:
    XMLDirector(XMLBuilder*, std::string);

    void construct();
    dom::Document* getResult();
};

#endif // XML_DIRECTOR_HPP
