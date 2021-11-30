#include "XMLDirector.hpp"
#include <iostream>

XMLDirector::XMLDirector(XMLBuilder* builder, std::string fileName)
    : factory(builder), tokenizer(fileName), currentState(nullptr) {}

dom::Document* XMLDirector::getResult() {
    return factory->getDocument();
}

void XMLDirector::construct() {

    std::string name = "";
    bool tagCloseStart = false; // flag to determine if element inside tag

    XMLTokenizer::XMLToken* token = tokenizer.getNextToken();
    // XMLTokenizer::XMLToken::TokenTypes tokenType = token->getTokenType();
    State* state = new XMLDirector::InsideAttrName;
    state->process(nullptr, token, token->getTokenType(), factory);

    while (token->getTokenType() != XMLTokenizer::XMLToken::NULL_TOKEN) {

        switch (token->getTokenType()) {

            case XMLTokenizer::XMLToken::ATTRIBUTE: {

                std::cout << "ATTRIBUTE\n";
                factory->addAttrName(token->getToken());
                break;
            }

            case XMLTokenizer::XMLToken::ATTRIBUTE_VALUE: {
                if (factory->getElement()) {
                    std::cout << "ATTRIBUTE_VALUE\n";
                    factory->addAttrValue(token->getToken());
                }
                break;
            }

            case XMLTokenizer::XMLToken::ELEMENT: {

                std::cout << "ELEMENT\n";
                if (!tagCloseStart) {
                    factory->setElement(factory->addElement(token->getToken()));
                } else {
                    factory->setElement(factory->getElementParent());
                }
                break;
            }

            case XMLTokenizer::XMLToken::VALUE: {

                std::cout << "VALUE\n";
                factory->addText(token->getToken());
                break;
            }

            case XMLTokenizer::XMLToken::TAG_CLOSE_START: {

                std::cout << "TAG_CLOSE_START\n";
                tagCloseStart = true;
                break;
            }

            case XMLTokenizer::XMLToken::TAG_END: {

                std::cout << "TAG_END\n";
                tagCloseStart = false;
                break;
            }

            case XMLTokenizer::XMLToken::NULL_TAG_END: {

                std::cout << "NULL_TAG_END\n";
                factory->setElement(factory->getElementParent());
                break;
            }

            default: {
                // do nothing
                break;
            }
        }

        // std::cout << factory->getElement() << '\n';

        delete token;
        token = tokenizer.getNextToken();
        // tokenType = token->getTokenType();
        // state = state->process(nullptr, token, token->getTokenType(),
        // factory);
    }

    delete token;
}

XMLDirector::State* XMLDirector::TagCloseStart::process(
    dom::Element*, XMLTokenizer::XMLToken* token,
    XMLTokenizer::XMLToken::TokenTypes, XMLBuilder* factory) {

    XMLDirector::State* state = this;

    std::cout << "TagCloseStart ";
    switch (token->getTokenType()) {

        case XMLTokenizer::XMLToken::ELEMENT: {
            std::cout << "ELEMENT\n";
            factory->setElement(factory->getElementParent());
            state = new XMLDirector::InsideAttrName;
            break;
        }

        default: {
            break;
        }
    }
    return state;
}

XMLDirector::State*
XMLDirector::TagCloseEnd::process(dom::Element*, XMLTokenizer::XMLToken* token,
                                  XMLTokenizer::XMLToken::TokenTypes,
                                  XMLBuilder* factory) {

    XMLDirector::State* state = this;

    std::cout << "TagCloseEnd ";
    switch (token->getTokenType()) {

        case XMLTokenizer::XMLToken::ELEMENT: {
            std::cout << "ELEMENT\n";
            factory->setElement(factory->addElement(token->getToken()));
            state = new XMLDirector::InsideAttrName;
            break;
        }

        default: {
            break;
        }
    }
    return state;
}

XMLDirector::State* XMLDirector::InsideAttrName::process(
    dom::Element*, XMLTokenizer::XMLToken* token,
    XMLTokenizer::XMLToken::TokenTypes, XMLBuilder* factory) {

    XMLDirector::State* state = this;

    std::cout << "InsideAttrName ";

    switch (token->getTokenType()) {

        case XMLTokenizer::XMLToken::ATTRIBUTE: {

            std::cout << "ATTRIBUTE\n";
            factory->addAttrName(token->getToken());
            break;
        }

        case XMLTokenizer::XMLToken::ATTRIBUTE_VALUE: {
            if (factory->getElement()) {
                std::cout << "ATTRIBUTE_VALUE\n";
                factory->addAttrValue(token->getToken());
            }
            break;
        }

        case XMLTokenizer::XMLToken::VALUE: {

            std::cout << "VALUE\n";
            factory->addText(token->getToken());
            break;
        }

        case XMLTokenizer::XMLToken::TAG_CLOSE_START: {
            state = new XMLDirector::TagCloseStart;
            break;
        }

        case XMLTokenizer::XMLToken::TAG_END: {
            state = new XMLDirector::TagCloseEnd;
            break;
        }

        case XMLTokenizer::XMLToken::NULL_TAG_END: {

            std::cout << "NULL_TAG_END\n";
            factory->setElement(factory->getElementParent());
            break;
        }

        default: {
            // do nothing
            break;
        }
    }

    return state;
}
