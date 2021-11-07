#ifndef NAMED_NODE_MAP_HPP
#define NAMED_NODE_MAP_HPP

#include "NodeList.hpp"
#include <string>

namespace dom {
class Document;

class NamedNodeMap : public NodeList {
public:
    virtual Node* getNamedItem(const std::string&) {
        return nullptr;
    }
    virtual Node* setNamedItem(Node*) {
        return nullptr;
    }
    virtual Node* removeNamedItem(const std::string&) {
        return nullptr;
    }
};
}; // namespace dom

class NamedNodeMap_Impl : public virtual dom::NamedNodeMap {
private:
    dom::Document* document;

public:
    NamedNodeMap_Impl(dom::Document*);

    virtual ~NamedNodeMap_Impl();

    virtual dom::Node* getNamedItem(const std::string&) override;
    virtual dom::Node* setNamedItem(dom::Node*) override;
    virtual dom::Node* removeNamedItem(const std::string&) override;
};

#endif // NAMEDNODEMAP_HPP
