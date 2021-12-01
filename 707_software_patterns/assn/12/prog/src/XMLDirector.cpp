#include "XMLDirector.hpp"

XMLDirector::State* XMLDirector::currentState = new XMLDirector::NoOp;
bool XMLDirector::lastTagState = false;

XMLDirector::XMLDirector(XMLBuilder* builder, std::string fileName)
    : factory(builder), tokenizer(fileName) {}

dom::Document* XMLDirector::getResult() {
    return factory->getDocument();
}

void XMLDirector::construct() {

    XMLTokenizer::XMLToken* token = tokenizer.getNextToken();

    while (token->getTokenType() != XMLTokenizer::XMLToken::NULL_TOKEN) {

        delete currentState;

        switch (token->getTokenType()) {

            case XMLTokenizer::XMLToken::ATTRIBUTE:
            case XMLTokenizer::XMLToken::ATTRIBUTE_VALUE: {

                currentState = new XMLDirector::InsideAttr;
                break;
            }

            case XMLTokenizer::XMLToken::ELEMENT: {

                currentState = new XMLDirector::InsideElement;
                break;
            }

            case XMLTokenizer::XMLToken::VALUE: {

                currentState = new XMLDirector::AddText;
                break;
            }

            case XMLTokenizer::XMLToken::TAG_CLOSE_START:
            case XMLTokenizer::XMLToken::TAG_END: {

                currentState = new XMLDirector::ParseTag;
                break;
            }

            case XMLTokenizer::XMLToken::NULL_TAG_END: {

                currentState = new XMLDirector::InNullTagEnd;
                break;
            }

            default: {
                currentState = new XMLDirector::NoOp;
                break;
            }
        }

        currentState->process(token, factory);
        delete token;
        token = tokenizer.getNextToken();
    }

    delete token;
}

void XMLDirector::NoOp::process(XMLTokenizer::XMLToken*, XMLBuilder*) {}

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

            if (!lastTagState) {
                factory->setElement(factory->addElement(token->getToken()));
            } else if (lastTagState) {
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

void XMLDirector::ParseTag::process(XMLTokenizer::XMLToken* token,
                                    XMLBuilder*) {

    currentState = this;

    switch (token->getTokenType()) {

        case XMLTokenizer::XMLToken::TAG_CLOSE_START: {

            lastTagState = true;
            break;
        }

        case XMLTokenizer::XMLToken::TAG_END: {

            lastTagState = false;
            break;
        }

        default: {
            delete currentState;
            currentState = new XMLDirector::NoOp;
        }
    }
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
