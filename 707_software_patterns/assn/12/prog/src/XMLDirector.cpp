#include "XMLDirector.hpp"

XMLDirector::State* XMLDirector::currentState = new XMLDirector::NoOp;
XMLDirector::State* XMLDirector::lastTagState = new XMLDirector::NoOp;

XMLDirector::XMLDirector(XMLBuilder* builder, std::string fileName)
    : factory(builder), tokenizer(fileName) {}

dom::Document* XMLDirector::getResult() {
    return factory->getDocument();
}

void XMLDirector::construct() {

    XMLTokenizer::XMLToken* token = tokenizer.getNextToken();

    while (token->getTokenType() != XMLTokenizer::XMLToken::NULL_TOKEN) {

        switch (token->getTokenType()) {

            case XMLTokenizer::XMLToken::ATTRIBUTE:
            case XMLTokenizer::XMLToken::ATTRIBUTE_VALUE: {

                delete currentState;
                currentState = new XMLDirector::InsideAttr;
                break;
            }

            case XMLTokenizer::XMLToken::ELEMENT: {

                delete currentState;
                currentState = new XMLDirector::InsideElement;
                break;
            }

            case XMLTokenizer::XMLToken::VALUE: {

                delete currentState;
                currentState = new XMLDirector::AddText;
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

                delete currentState;
                currentState = new XMLDirector::InNullTagEnd;
                break;
            }

            default: {
                // do nothing
                break;
            }
        }

        currentState->process(token, factory);
        delete token;
        token = tokenizer.getNextToken();
    }

    delete token;
}

void XMLDirector::InsideAttr::process(XMLTokenizer::XMLToken* token,
                                      XMLBuilder* factory) {

    currentState = this;

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
            delete currentState;
            currentState = new XMLDirector::NoOp;
        }
    }
}

void XMLDirector::InsideElement::process(XMLTokenizer::XMLToken* token,
                                         XMLBuilder* factory) {

    currentState = this;

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
            delete currentState;
            currentState = new XMLDirector::NoOp;
        }
    }
}

void XMLDirector::NoOp::process(XMLTokenizer::XMLToken*, XMLBuilder*) {
    currentState = this;
}

void XMLDirector::TagCloseStart::process(XMLTokenizer::XMLToken*, XMLBuilder*) {
    currentState = this;
}

void XMLDirector::TagCloseEnd::process(XMLTokenizer::XMLToken*, XMLBuilder*) {
    currentState = this;
}

void XMLDirector::AddText::process(XMLTokenizer::XMLToken* token,
                                   XMLBuilder* factory) {

    currentState = this;

    switch (token->getTokenType()) {

        case XMLTokenizer::XMLToken::VALUE: {

            factory->addText(token->getToken());
            break;
        }

        default: {
            delete currentState;
            currentState = new XMLDirector::NoOp;
        }
    }
}

void XMLDirector::InNullTagEnd::process(XMLTokenizer::XMLToken* token,
                                        XMLBuilder* factory) {

    currentState = this;

    switch (token->getTokenType()) {

        case XMLTokenizer::XMLToken::NULL_TAG_END: {

            factory->setElement(factory->getElementParent());
            break;
        }

        default: {
            delete currentState;
            currentState = new XMLDirector::NoOp;
        }
    }
}
