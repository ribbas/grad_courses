#include "XMLBuilder.hpp"
#include "XMLTokenizer.hpp"
#include <iostream>

XMLBuilder::XMLBuilder() {
    domFactory = new Document_Impl;
}

void XMLBuilder::beginDocument() {
    document = new Document_Impl;
    // We have a document, now make it the concrete factory!
    std::cout << "init!\n";
    domFactory = document;
}

// dom::Element* XMLBuilder::addElement(dom::Element* element,
//                                      std::string elementName) {
//     std::cout << "ele " << element->hasChildNodes() << std::endl;
//     dom::Element* newElement = domFactory->createElement(elementName);
//     element->appendChild(newElement);
//     return newElement;
// }

dom::Element* XMLBuilder::addElement(dom::Element* element,
                                     std::string elementName) {

    dom::Element* newElement;
    if (!elementVec.size()) {
        beginDocument();
        newElement = domFactory->createElement(elementName);
        std::cout << "doc " << std::endl;
        document->appendChild(newElement);
    } else {
        newElement = domFactory->createElement(elementName);
        element->appendChild(newElement);
        std::cout << "elem " << std::endl;
    }

    elementVec.push_back(newElement);
    return newElement;
}

dom::Attr* XMLBuilder::addAttribute(dom::Element* element, std::string attrName,
                                    std::string attrValue) {
    dom::Attr* newAttribute = domFactory->createAttribute(attrName);
    newAttribute->setValue(attrValue);
    element->setAttributeNode(newAttribute);
    return newAttribute;
}

dom::Text* XMLBuilder::addText(dom::Element* element, std::string text) {
    dom::Text* newText = domFactory->createTextNode(text);
    element->appendChild(newText);
    return newText;
}

dom::Document* XMLDirector::parseFile(std::string fileName) {

    XMLTokenizer tokenizer(fileName);

    XMLTokenizer::XMLToken* token = tokenizer.getNextToken();
    // dom::Document* document = 0;
    dom::Element* currElt = 0;
    bool firstElt = true, tagCloseStart = false;
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
                if (currElt != 0) {
                    builder->addAttribute(currElt, attrName, token->getToken());
                    attrName = "";
                }
                break;
            }

            case XMLTokenizer::XMLToken::ELEMENT: {
                std::cout << "XMLTokenizer::XMLToken::ELEMENT "
                          << token->getToken() << std::endl;

                if (!tagCloseStart) {
                    currElt = builder->addElement(currElt, token->getToken());
                } else {
                    currElt =
                        dynamic_cast<dom::Element*>(currElt->getParentNode());
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

                currElt = dynamic_cast<dom::Element*>(currElt->getParentNode());
                break;
            }

            case XMLTokenizer::XMLToken::VALUE: {
                std::cout << "XMLTokenizer::XMLToken::VALUE "
                          << token->getToken() << std::endl;

                builder->addText(currElt, token->getToken());
                break;
            }

            case XMLTokenizer::XMLToken::TAG_END: {
                std::cout << "XMLTokenizer::XMLToken::TAG_END "
                          << token->getToken() << std::endl;

                if (tagCloseStart)
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
    return builder->getDocument();
}