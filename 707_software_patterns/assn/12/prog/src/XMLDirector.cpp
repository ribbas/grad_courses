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
    State* state = new XMLDirector::InsideAttrName;

    while (token->getTokenType() != XMLTokenizer::XMLToken::NULL_TOKEN) {

        // switch (token->getTokenType()) {

        //     case XMLTokenizer::XMLToken::ATTRIBUTE: {

        //         std::cout << "ATTRIBUTE\n";
        //         factory->addAttrName(token->getToken());
        //         break;
        //     }

        //     case XMLTokenizer::XMLToken::ATTRIBUTE_VALUE: {
        //         std::cout << "ATTRIBUTE_VALUE\n";
        //         if (factory->getElement()) {
        //             std::cout << "ATTRIBUTE_VALUE success\n";
        //             factory->addAttrValue(token->getToken());
        //         }
        //         break;
        //     }

        //     case XMLTokenizer::XMLToken::ELEMENT: {

        //         std::cout << "ELEMENT\n";
        //         if (!tagCloseStart) {
        //             std::cout << "ELEMENT tag end\n";
        //             factory->setElement(factory->addElement(token->getToken()));
        //         } else {
        //             std::cout << "ELEMENT tag close start\n";
        //             factory->setElement(factory->getElementParent());
        //         }
        //         break;
        //     }

        //     case XMLTokenizer::XMLToken::VALUE: {

        //         std::cout << "VALUE\n";
        //         factory->addText(token->getToken());
        //         break;
        //     }

        //     case XMLTokenizer::XMLToken::TAG_CLOSE_START: {

        //         std::cout << "TAG_CLOSE_START\n";
        //         tagCloseStart = true;
        //         break;
        //     }

        //     case XMLTokenizer::XMLToken::TAG_END: {

        //         std::cout << "TAG_END\n";
        //         tagCloseStart = false;
        //         break;
        //     }

        //     case XMLTokenizer::XMLToken::NULL_TAG_END: {

        //         std::cout << "NULL_TAG_END\n";
        //         factory->setElement(factory->getElementParent());
        //         break;
        //     }

        //     default: {
        //         // do nothing
        //         break;
        //     }
        // }

        // std::cout << factory->getElement() << '\n';

        state = state->process(token, factory, tagCloseStart);
        delete token;
        token = tokenizer.getNextToken();
    }

    delete token;
}

XMLDirector::State*
XMLDirector::TagCloseStart::process(XMLTokenizer::XMLToken* token,
                                    XMLBuilder* factory, bool&) {

    XMLDirector::State* state = this;

    std::cout << "TagCloseStart ";
    switch (token->getTokenType()) {

        case XMLTokenizer::XMLToken::ELEMENT: {
            std::cout << "ELEMENT\n";
            factory->setElement(factory->getElementParent());
            delete state;
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
XMLDirector::TagCloseEnd::process(XMLTokenizer::XMLToken* token,
                                  XMLBuilder* factory, bool&) {

    XMLDirector::State* state = this;

    std::cout << "TagCloseEnd ";
    switch (token->getTokenType()) {

        case XMLTokenizer::XMLToken::ELEMENT: {
            std::cout << "ELEMENT\n";
            factory->setElement(factory->addElement(token->getToken()));
            delete state;
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
XMLDirector::InsideAttrName::process(XMLTokenizer::XMLToken* token,
                                     XMLBuilder* factory, bool& tagCloseStart) {

    XMLDirector::State* state = this;

    // std::cout << "InsideAttrName ";

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

        case XMLTokenizer::XMLToken::ELEMENT: {

            std::cout << "ELEMENT ";
            if (!tagCloseStart) {
                std::cout << "tag end";
                factory->setElement(factory->addElement(token->getToken()));
            } else {
                std::cout << "tag close start";
                factory->setElement(factory->getElementParent());
            }
            std::cout << '\n';
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

    return state;
}
