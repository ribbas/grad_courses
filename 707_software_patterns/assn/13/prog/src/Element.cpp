#include "Element.hpp"
#include "Attr.hpp"
#include "Document.hpp"
#include "Text.hpp"
#include <iostream>

Element_Impl::Element_Impl(const std::string& tagName, dom::Document* document)
    : Node_Impl(tagName, dom::Node::ELEMENT_NODE, document),
      attributes(document) {}

Element_Impl::~Element_Impl() {
    for (dom::Node* i : attributes) {
        delete i;
    }
}

const std::string& Element_Impl::getAttribute(const std::string& name) {
    for (dom::NodeList::iterator i = attributes.begin(); i != attributes.end();
         i++) {
        dom::Attr* attr = dynamic_cast<dom::Attr*>(*i.operator->());

        if (attr->getName().compare(name) == 0) {
            return attr->getValue();
        }
    }

    static const std::string empty_string("");
    return empty_string;
}

dom::Attr* Element_Impl::getAttributeNode(const std::string& name) {
    for (dom::NodeList::iterator i = attributes.begin(); i != attributes.end();
         i++) {
        dom::Attr* attr = dynamic_cast<dom::Attr*>(*i.operator->());

        if (attr->getName().compare(name) == 0) {
            return attr;
        }
    }

    return 0;
}

dom::NodeList* Element_Impl::getElementsByTagName(const std::string& tagName) {
    dom::NodeList* nodeList = new dom::NodeList();

    for (dom::NodeList::iterator i = getChildNodes()->begin();
         i != getChildNodes()->end(); i++) {
        dom::Element* element;

        if ((element = dynamic_cast<dom::Element*>(*i.operator->())) &&
            element->getTagName().compare(tagName) == 0) {
            nodeList->push_back(*i.operator->());
        }
    }

    return nodeList;
}

const std::string& Element_Impl::getTagName() {
    return getNodeName();
}

bool Element_Impl::hasAttribute(const std::string& name) {
    for (dom::NodeList::iterator i = attributes.begin(); i != attributes.end();
         i++) {
        dom::Attr* attr = dynamic_cast<dom::Attr*>(*i.operator->());

        if (attr->getName().compare(name) == 0) {
            return true;
        }
    }

    return false;
}

void Element_Impl::removeAttribute(const std::string& name) {
    for (dom::NodeList::iterator i = attributes.begin(); i != attributes.end();
         i++) {
        dom::Attr* attr = dynamic_cast<dom::Attr*>(*i.operator->());

        if (attr->getName().compare(name) == 0) {
            attributes.erase(i);
            return;
        }
    }
}

dom::Attr* Element_Impl::removeAttributeNode(dom::Attr* oldAttr) {
    for (dom::NodeList::iterator i = attributes.begin(); i != attributes.end();
         i++)
        if (*i.operator->() == oldAttr) {
            dom::Attr* attribute = (dom::Attr*)i.operator->();
            attributes.erase(i);
            return attribute;
        }

    throw dom::DOMException(dom::DOMException::NOT_FOUND_ERR,
                            "Attribute not found.");
}

void Element_Impl::setAttribute(const std::string& name,
                                const std::string& value) {
    for (dom::NodeList::iterator i = attributes.begin(); i != attributes.end();
         i++) {
        dom::Attr* attr = dynamic_cast<dom::Attr*>(*i.operator->());

        if (attr->getName().compare(name) == 0) {
            attr->setValue(value);
            return;
        }
    }

    dom::Attr* attribute;
    attributes.push_back(
        attribute = new Attr_Impl(
            name, value, dynamic_cast<Document_Impl*>(getOwnerDocument())));
    dynamic_cast<Node_Impl*>(dynamic_cast<Node*>(attribute))->setParent(this);
}

dom::Attr* Element_Impl::setAttributeNode(dom::Attr* newAttr) {
    if (newAttr->getOwnerDocument() != getOwnerDocument()) {
        throw dom::DOMException(dom::DOMException::WRONG_DOCUMENT_ERR,
                                "Attribute not created by this document.");
    }

    if (newAttr->getParentNode() != 0) {
        throw dom::DOMException(dom::DOMException::INUSE_ATTRIBUTE_ERR,
                                "Attribute in use by other element.");
    }

    dom::Attr* oldAttribute = nullptr;

    for (dom::NodeList::iterator i = attributes.begin(); i != attributes.end();
         i++) {
        if (dynamic_cast<dom::Attr*>(*i)->getName().compare(
                newAttr->getName()) == 0) {
            oldAttribute = (dom::Attr*)i.operator->();
            attributes.erase(i);
            break;
        }
    }

    dynamic_cast<Node_Impl*>(dynamic_cast<Node*>(newAttr))->setParent(this);
    attributes.push_back(newAttr);
    return oldAttribute;
}

dom::NamedNodeMap* Element_Impl::getAttributes() {
    return &attributes;
}

bool Element_Impl::hasAttributes() {
    return attributes.size() > 0;
}

void Element_Impl::serialize(std::fstream* writer,
                             WhitespaceStrategy* whitespace) {
    whitespace->prettyIndentation(writer);
    *writer << "<" << getTagName();

    int attrCount = 0;

    for (dom::NamedNodeMap::iterator i = getAttributes()->begin();
         i != getAttributes()->end(); i++) {
        (*i)->serialize(writer, whitespace);
        attrCount++;
    }

    if (attrCount > 0) {
        *writer << " ";
    }

    if (getChildNodes()->size() == 0) {
        *writer << "/>";
        whitespace->newLine(writer);
    } else {
        *writer << ">";
        whitespace->newLine(writer);
        whitespace->incrementIndentation();

        for (dom::NodeList::iterator i = getChildNodes()->begin();
             i != getChildNodes()->end(); i++) {
            if (dynamic_cast<dom::Element*>(*i) != 0 ||
                dynamic_cast<dom::Text*>(*i) != 0) {
                (*i)->serialize(writer, whitespace);
            }
        }

        whitespace->decrementIndentation();
        whitespace->prettyIndentation(writer);
        *writer << "</" << getTagName() + ">";
        whitespace->newLine(writer);
    }
}

bool Element_Impl::handleEvent(dom::Event* event) {
    if (getAttribute("message") == event->message) {
        std::cout << "Event: " << event->message << " handled by " << this
                  << '\n';
        return true;
    } else if (dynamic_cast<dom::Element*>(getParentNode()) != nullptr) {
        dynamic_cast<dom::Element*>(getParentNode())->handleEvent(event);
    } else {
        std::cout << "Event was not handled\n";
    }
    return false;
}
