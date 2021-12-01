#include "XMLDirector.hpp"

XMLDirector::XMLDirector(XMLBuilder* builder, std::string fileName)
    : factory(builder), tokenizer(fileName), currentState(nullptr) {}

dom::Document* XMLDirector::getResult() {
    return factory->getDocument();
}

void XMLDirector::construct() {

    XMLTokenizer::XMLToken* token = tokenizer.getNextToken();
    State* state = new XMLDirector::NoOp;
    State* lastTagState = new XMLDirector::NoOp;

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

                delete state;
                state = new XMLDirector::AddText;
                break;
            }

            case XMLTokenizer::XMLToken::TAG_CLOSE_START: {

                delete lastTagState;
                lastTagState = new XMLDirector::TagCloseStart;
                break;
            }

            case XMLTokenizer::XMLToken::TAG_END: {

                delete lastTagState;
                lastTagState = new XMLDirector::TagCloseEnd;
                break;
            }

            case XMLTokenizer::XMLToken::NULL_TAG_END: {

                delete state;
                state = new XMLDirector::InNullTagEnd;
                break;
            }

            default: {
                // do nothing
                break;
            }
        }

        state = state->process(lastTagState, token, factory);
        delete token;
        token = tokenizer.getNextToken();
    }

    delete token;
}

XMLDirector::State*
XMLDirector::InsideAttr::process(State*, XMLTokenizer::XMLToken* token,
                                 XMLBuilder* factory) {

    XMLDirector::State* state = this;

    switch (token->getTokenType()) {

        case XMLTokenizer::XMLToken::ATTRIBUTE: {

            factory->addAttrName(token->getToken());
            break;
        }

        case XMLTokenizer::XMLToken::ATTRIBUTE_VALUE: {
            if (factory->getElement()) {
                factory->addAttrValue(token->getToken());
            }
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
    State* lastTagState, XMLTokenizer::XMLToken* token, XMLBuilder* factory) {

    XMLDirector::State* state = this;

    switch (token->getTokenType()) {

        case XMLTokenizer::XMLToken::ELEMENT: {

            if (dynamic_cast<TagCloseEnd*>(lastTagState)) {
                factory->setElement(factory->addElement(token->getToken()));
            } else if (dynamic_cast<TagCloseStart*>(lastTagState)) {
                factory->setElement(factory->getElementParent());
            }
            break;
        }

        default: {
            delete state;
            state = new XMLDirector::NoOp;
        }
    }

    return state;
}

XMLDirector::State* XMLDirector::NoOp::process(State*, XMLTokenizer::XMLToken*,
                                               XMLBuilder*) {
    return this;
}

XMLDirector::State* XMLDirector::TagCloseStart::process(State*,
                                                        XMLTokenizer::XMLToken*,
                                                        XMLBuilder*) {
    return this;
}

XMLDirector::State* XMLDirector::TagCloseEnd::process(State*,
                                                      XMLTokenizer::XMLToken*,
                                                      XMLBuilder*) {
    return this;
}

XMLDirector::State* XMLDirector::AddText::process(State*,
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
XMLDirector::State*
XMLDirector::InNullTagEnd::process(State*, XMLTokenizer::XMLToken* token,
                                   XMLBuilder* factory) {

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
