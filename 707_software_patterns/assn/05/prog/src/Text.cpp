#include "Text.hpp"
#include <stdexcept>

Text_Impl::Text_Impl(const std::string value, dom::Document* document)
    : Node_Impl("", dom::Node::TEXT_NODE) {
    setNodeValue(value);
    Node_Impl::document = document;
}

Text_Impl::~Text_Impl() {}

const std::string& Text_Impl::getName() {
    return getNodeName();
}

const std::string& Text_Impl::getData() {
    return getNodeValue();
}

const std::string& Text_Impl::getValue() {
    return getData();
}

void Text_Impl::setData(const std::string& value) {
    setNodeValue(value);
}

void Text_Impl::setValue(const std::string& value) {
    setNodeValue(value);
}

int Text_Impl::getLength() {
    return getValue().size();
}

const std::string& Text_Impl::substringData(int streamPos, int count) {
    try {
        //
        // This is not thread-safe, of course.
        //
        static std::string value;
        value = getValue().substr(streamPos, count);

        return value;
    } catch (std::out_of_range&) {
        throw dom::DOMException(dom::DOMException::INDEX_SIZE_ERR,
                                "Index larger than Text node's value.");
    }
}

void Text_Impl::appendData(const std::string& arg) {
    std::string value = getValue();

    setValue(value.append(arg));
}

void Text_Impl::insertData(int streamPos, const std::string& arg) {
    std::string value = getValue();

    setValue(value.insert(streamPos, arg));
}

void Text_Impl::deleteData(int streamPos, int count) {
    std::string value = getValue();

    setValue(value.erase(streamPos, count));
}

void Text_Impl::replaceData(int streamPos, int count, const std::string& arg) {
    std::string value = getValue();

    setValue(value.erase(streamPos, count).insert(streamPos, arg));
}

dom::Text* Text_Impl::splitText(int streamPos) {
    try {
        dom::Text* text = new Text_Impl(
            substringData(streamPos, getLength() - streamPos), document);

        setValue(substringData(0, streamPos));

        if (getParentNode() != 0) {
            insertBefore(text, getNextSibling());
        }

        return text;
    } catch (std::out_of_range&) {
        throw dom::DOMException(dom::DOMException::INDEX_SIZE_ERR,
                                "Index larget than Text node's value.");
    }
}

dom::Node* Text_Impl::insertBefore(dom::Node*, dom::Node*) {
    throw dom::DOMException(dom::DOMException::HIERARCHY_REQUEST_ERR,
                            "Text nodes do not support this method.");
}

dom::Node* Text_Impl::replaceChild(dom::Node*, dom::Node*) {
    throw dom::DOMException(dom::DOMException::HIERARCHY_REQUEST_ERR,
                            "Text nodes do not support this method.");
}

dom::Node* Text_Impl::removeChild(dom::Node*) {
    throw dom::DOMException(dom::DOMException::HIERARCHY_REQUEST_ERR,
                            "Text nodes do not support this method.");
}

dom::Node* Text_Impl::appendChild(dom::Node*) {
    throw dom::DOMException(dom::DOMException::HIERARCHY_REQUEST_ERR,
                            "Text nodes do not support this method.");
}

void Text_Impl::serialize(std::fstream* writer,
                          WhitespaceStrategy* whitespace) {
    whitespace->prettyIndentation(writer);
    *writer << getData();
    whitespace->newLine(writer);
}
