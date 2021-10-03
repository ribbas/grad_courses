#include "XMLBuilder.hpp"
#include <iostream>

std::string& XMLBuilder::ltrim(std::string& s) {
    std::string::iterator it = std::find_if(s.begin(), s.end(), [](char c) {
        return !std::isspace<char>(c, std::locale::classic());
    });
    s.erase(s.begin(), it);
    return s;
}

XMLBuilder::XMLBuilder()
    : document(new Document_Impl), currentElement(nullptr) {}

void XMLBuilder::setElement(dom::Element* element) {

    if (element) {
        currentElement = element;
    }
}

dom::Element* XMLBuilder::getElementParent() {
    return dynamic_cast<dom::Element*>(currentElement->getParentNode());
}

dom::Element* XMLBuilder::addElement(std::string tagName) {

    dom::Element* newElement = document->createElement(tagName);

    if (!currentElement) {
        document->appendChild(newElement);
    } else {
        currentElement->appendChild(newElement);
    }

    return newElement;
}

dom::Attr* XMLBuilder::addAttribute(std::string name, std::string value) {
    name = ltrim(name);
    value = ltrim(value);
    value = value.substr(1, value.size() - 2);

    dom::Attr* newAttribute = document->createAttribute(name);
    newAttribute->setValue(value);
    currentElement->setAttributeNode(newAttribute);
    return newAttribute;
}

dom::Text* XMLBuilder::addText(std::string data) {

    data = ltrim(data);

    dom::Text* newText = document->createTextNode(data);
    currentElement->appendChild(newText);
    return newText;
}

void XMLDirector::construct() {

    XMLTokenizer::XMLToken* token = tokenizer.getNextToken();
    dom::Element* element = nullptr;
    bool tagCloseStart = false;
    std::string attrName = "";

    while (token->getTokenType() != XMLTokenizer::XMLToken::NULL_TOKEN) {

        switch (token->getTokenType()) {

            case XMLTokenizer::XMLToken::ATTRIBUTE: {
                std::cout << "XMLTokenizer::XMLToken::ATTRIBUTE "
                          << token->getToken() << std::endl;

                attrName = token->getToken();
                break;
            }

            case XMLTokenizer::XMLToken::ATTRIBUTE_VALUE: {
                std::cout << "XMLTokenizer::XMLToken::ATTRIBUTE_VALUE "
                          << token->getToken() << std::endl;
                if (element) {
                    factory->setElement(element);
                    factory->addAttribute(attrName, token->getToken());
                }
                break;
            }

            case XMLTokenizer::XMLToken::ELEMENT: {
                std::cout << "XMLTokenizer::XMLToken::ELEMENT "
                          << token->getToken() << std::endl;

                if (!tagCloseStart) {
                    std::cout << "pushing elemennt " << element << '\n';
                    factory->setElement(element);
                    element = factory->addElement(token->getToken());
                } else {
                    element = factory->getElementParent();
                }
                break;
            }

            case XMLTokenizer::XMLToken::TAG_CLOSE_START: {
                std::cout << "XMLTokenizer::XMLToken::TAG_CLOSE_START "
                          << token->getToken() << std::endl;

                tagCloseStart = true;
                break;
            }

            case XMLTokenizer::XMLToken::NULL_TAG_END: {
                std::cout << "XMLTokenizer::XMLToken::NULL_TAG_END "
                          << token->getToken() << std::endl;

                element = factory->getElementParent();
                break;
            }

            case XMLTokenizer::XMLToken::VALUE: {
                std::cout << "XMLTokenizer::XMLToken::VALUE "
                          << token->getToken() << std::endl;

                factory->setElement(element);
                factory->addText(token->getToken());
                break;
            }

            case XMLTokenizer::XMLToken::TAG_END: {
                std::cout << "XMLTokenizer::XMLToken::TAG_END "
                          << token->getToken() << std::endl;

                tagCloseStart = false;
                break;
            }

            default: {
                break;
            }
        }

        delete token;
        token = tokenizer.getNextToken();
    }

    delete token;
    delete element;
}
