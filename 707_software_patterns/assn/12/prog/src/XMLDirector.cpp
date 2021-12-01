#include "XMLDirector.hpp"
#include <iostream>

XMLDirector::XMLDirector(XMLBuilder* builder, std::string fileName)
    : factory(builder), tokenizer(fileName), currentState(nullptr) {}

dom::Document* XMLDirector::getResult() {
    return factory->getDocument();
}

void XMLDirector::construct() {

    XMLTokenizer::XMLToken* token = tokenizer.getNextToken();
    State* state = new XMLDirector::NoOp;
    State* lastState = new XMLDirector::NoOp;

    while (token->getTokenType() != XMLTokenizer::XMLToken::NULL_TOKEN) {

        switch (token->getTokenType()) {

            case XMLTokenizer::XMLToken::ATTRIBUTE:
            case XMLTokenizer::XMLToken::ATTRIBUTE_VALUE: {

                delete state;
                state = new XMLDirector::InsideAttr;
                break;
            }

            case XMLTokenizer::XMLToken::ELEMENT: {

                delete state;
                state = new XMLDirector::InsideElement;
                break;
            }

            case XMLTokenizer::XMLToken::VALUE: {

                std::cout << "VALUE\n";
                delete state;
                state = new XMLDirector::AddText;

                break;
            }

            case XMLTokenizer::XMLToken::TAG_CLOSE_START: {

                std::cout << "TAG_CLOSE_START\n";
                delete lastState;
                lastState = new XMLDirector::TagCloseStart;
                break;
            }

            case XMLTokenizer::XMLToken::TAG_END: {

                std::cout << "TAG_END\n";
                delete lastState;
                lastState = new XMLDirector::TagCloseEnd;
                break;
            }

            case XMLTokenizer::XMLToken::NULL_TAG_END: {

                std::cout << "NULL_TAG_END\n";
                delete state;
                state = new XMLDirector::InNullTagEnd;
                break;
            }

            default: {
                // do nothing
                break;
            }
        }

        state = state->process(lastState, token, factory);
        delete token;
        token = tokenizer.getNextToken();
    }

    delete token;
}

XMLDirector::State* XMLDirector::InsideAttr::process(
    State* lastState, XMLTokenizer::XMLToken* token, XMLBuilder* factory) {

    XMLDirector::State* state = this;

    switch (token->getTokenType()) {

        case XMLTokenizer::XMLToken::ATTRIBUTE: {

            std::cout << "ATTRIBUTE\n";
            factory->addAttrName(token->getToken());
            break;
        }

        case XMLTokenizer::XMLToken::ATTRIBUTE_VALUE: {
            std::cout << "ATTRIBUTE_VALUE";
            if (factory->getElement()) {
                std::cout << " success";
                factory->addAttrValue(token->getToken());
            }
            std::cout << '\n';
            break;
        }
        default: {
            delete state;
            state = new XMLDirector::NoOp;
        }
    }

    return state;
}

XMLDirector::State* XMLDirector::InsideElement::process(
    State* lastState, XMLTokenizer::XMLToken* token, XMLBuilder* factory) {

    XMLDirector::State* state = this;

    switch (token->getTokenType()) {

        case XMLTokenizer::XMLToken::ELEMENT: {

            std::cout << "ELEMENT";
            if (dynamic_cast<TagCloseEnd*>(lastState)) {
                std::cout << " tag end";
                factory->setElement(factory->addElement(token->getToken()));
            } else if (dynamic_cast<TagCloseStart*>(lastState)) {
                std::cout << " tag close start";
                factory->setElement(factory->getElementParent());
            }
            std::cout << '\n';
            break;
        }

        default: {
            delete state;
            state = new XMLDirector::NoOp;
        }
    }

    return state;
}

XMLDirector::State* XMLDirector::NoOp::process(State* lastState,
                                               XMLTokenizer::XMLToken* token,
                                               XMLBuilder* factory) {

    XMLDirector::State* state = this;

    return state;
}

XMLDirector::State* XMLDirector::TagCloseStart::process(
    State* lastState, XMLTokenizer::XMLToken* token, XMLBuilder* factory) {

    XMLDirector::State* state = this;

    return state;
}

XMLDirector::State* XMLDirector::TagCloseEnd::process(
    State* lastState, XMLTokenizer::XMLToken* token, XMLBuilder* factory) {

    XMLDirector::State* state = this;

    return state;
}

XMLDirector::State* XMLDirector::AddText::process(State* lastState,
                                                  XMLTokenizer::XMLToken* token,
                                                  XMLBuilder* factory) {

    XMLDirector::State* state = this;

    switch (token->getTokenType()) {

        case XMLTokenizer::XMLToken::VALUE: {

            factory->addText(token->getToken());
            break;
        }

        default: {
            delete state;
            state = new XMLDirector::NoOp;
        }
    }

    return state;
}
XMLDirector::State* XMLDirector::InNullTagEnd::process(
    State* lastState, XMLTokenizer::XMLToken* token, XMLBuilder* factory) {

    XMLDirector::State* state = this;

    switch (token->getTokenType()) {

        case XMLTokenizer::XMLToken::NULL_TAG_END: {

            factory->setElement(factory->getElementParent());
            break;
        }

        default: {
            delete state;
            state = new XMLDirector::NoOp;
        }
    }

    return state;
}
