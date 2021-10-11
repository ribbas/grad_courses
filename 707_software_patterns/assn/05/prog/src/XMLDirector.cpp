#include "XMLDirector.hpp"

XMLDirector::XMLDirector(XMLBuilder* builder, std::string fileName)
    : factory(builder), tokenizer(fileName) {}

dom::Document* XMLDirector::getResult() {
    return factory->getDocument();
}

void XMLDirector::resumeParse(dom::Element* element) {

    std::string name = "";
    bool tagCloseStart = false; // flag to determine if element inside tag

    XMLTokenizer::XMLToken* token = tokenizer.getNextToken();
    XMLTokenizer::XMLToken::TokenTypes tokenType = token->getTokenType();

    while (tokenType != XMLTokenizer::XMLToken::NULL_TOKEN) {

        factory->setElement(element);

        switch (tokenType) {

            case XMLTokenizer::XMLToken::ATTRIBUTE: {

                name = token->getToken();
                break;
            }

            case XMLTokenizer::XMLToken::ATTRIBUTE_VALUE: {
                if (element) {
                    factory->addAttribute(name, token->getToken());
                }
                break;
            }

            case XMLTokenizer::XMLToken::ELEMENT: {

                if (!tagCloseStart) {
                    element = factory->addElement(token->getToken());
                } else {
                    element = factory->getElementParent();
                }
                break;
            }

            case XMLTokenizer::XMLToken::VALUE: {

                factory->addText(token->getToken());
                break;
            }

            case XMLTokenizer::XMLToken::TAG_CLOSE_START: {

                tagCloseStart = true;
                break;
            }

            case XMLTokenizer::XMLToken::TAG_END: {

                tagCloseStart = false;
                break;
            }

            case XMLTokenizer::XMLToken::NULL_TAG_END: {

                element = factory->getElementParent();
                break;
            }

            default: {
                // do nothing
                break;
            }
        }

        delete token;
        token = tokenizer.getNextToken();
        tokenType = token->getTokenType();
    }

    delete token;
    delete element;
}

void XMLDirector::construct() {

    dom::Element* element = nullptr;
    std::string name = "";
    bool tagCloseStart = false; // flag to determine if element inside tag

    XMLTokenizer::XMLToken* token = tokenizer.getNextToken();
    XMLTokenizer::XMLToken::TokenTypes tokenType = token->getTokenType();

    while (tokenType != XMLTokenizer::XMLToken::NULL_TOKEN) {

        factory->setElement(element);

        switch (tokenType) {

            case XMLTokenizer::XMLToken::ATTRIBUTE: {

                name = token->getToken();
                break;
            }

            case XMLTokenizer::XMLToken::ATTRIBUTE_VALUE: {
                if (element) {
                    factory->addAttribute(name, token->getToken());
                }
                break;
            }

            case XMLTokenizer::XMLToken::ELEMENT: {

                if (!tagCloseStart) {
                    element = factory->addElement(
                        token->getToken(), tokenizer.getStreamPos(), this);
                } else {
                    element = factory->getElementParent();
                }
                break;
            }

            case XMLTokenizer::XMLToken::VALUE: {

                factory->addText(token->getToken());
                break;
            }

            case XMLTokenizer::XMLToken::TAG_CLOSE_START: {

                tagCloseStart = true;
                break;
            }

            case XMLTokenizer::XMLToken::TAG_END: {

                tagCloseStart = false;
                break;
            }

            case XMLTokenizer::XMLToken::NULL_TAG_END: {

                element = factory->getElementParent();
                break;
            }

            default: {
                // do nothing
                break;
            }
        }

        delete token;
        token = tokenizer.getNextToken();
        tokenType = token->getTokenType();
    }

    delete token;
    delete element;
}
