#include "XMLBuilder.hpp"
#include <algorithm>

XMLBuilder::XMLBuilder()
    : document(new Document_Impl), currentElement(nullptr) {}

// this method was extracted and modified from
// https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/
std::string& XMLBuilder::ltrim(std::string& s) {

    std::string::iterator it = std::find_if(s.begin(), s.end(), [](char c) {
        return !std::isspace<char>(c, std::locale::classic());
    });
    s.erase(s.begin(), it);
    return s;
}

void XMLBuilder::trimAttr(std::string& name, std::string& value) {
    name = ltrim(name);
    name = name.substr(0, name.size() - 1);
    value = ltrim(value);
    value = value.substr(1, value.size() - 2);
}

void XMLBuilder::setElement(dom::Element* element) {

    if (element) {
        currentElement = element;
    }
}

dom::Element* XMLBuilder::getElementParent() {
    return dynamic_cast<dom::Element*>(currentElement->getParentNode());
}

dom::Document* XMLBuilder::getDocument() {
    return document;
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

    trimAttr(name, value);
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
