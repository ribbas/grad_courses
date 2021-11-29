#ifndef XML_DIRECTOR_HPP
#define XML_DIRECTOR_HPP

#include "XMLBuilder.hpp"
#include "XMLTokenizer.hpp"

class XMLDirector {
private:
    XMLBuilder* factory;
    XMLTokenizer tokenizer;

    struct State {
        virtual State* processToken(XMLTokenizer::XMLToken*,
                                    XMLTokenizer::XMLToken::TokenTypes,
                                    XMLTokenizer::XMLToken::TokenTypes,
                                    XMLBuilder*) = 0;
    };

    struct BeforeProlog : public State {
        virtual State* processToken(XMLTokenizer::XMLToken*,
                                    XMLTokenizer::XMLToken::TokenTypes,
                                    XMLTokenizer::XMLToken::TokenTypes,
                                    XMLBuilder*);
    };

    struct AfterProlog : public State {
        virtual State* processToken(XMLTokenizer::XMLToken*,
                                    XMLTokenizer::XMLToken::TokenTypes,
                                    XMLTokenizer::XMLToken::TokenTypes,
                                    XMLBuilder*);
    };

    struct ParsingElement : public State {
        virtual State* processToken(XMLTokenizer::XMLToken*,
                                    XMLTokenizer::XMLToken::TokenTypes,
                                    XMLTokenizer::XMLToken::TokenTypes,
                                    XMLBuilder*);
    };

    struct InNonnullElement : public State {
        virtual State* processToken(XMLTokenizer::XMLToken*,
                                    XMLTokenizer::XMLToken::TokenTypes,
                                    XMLTokenizer::XMLToken::TokenTypes,
                                    XMLBuilder*);
    };

    struct End : public State {
        virtual State* processToken(XMLTokenizer::XMLToken*,
                                    XMLTokenizer::XMLToken::TokenTypes,
                                    XMLTokenizer::XMLToken::TokenTypes,
                                    XMLBuilder*);
    };

    State* currentState;

public:
    XMLDirector(XMLBuilder*, std::string);

    void construct();
    dom::Document* getResult();
};

#endif // XML_DIRECTOR_HPP
