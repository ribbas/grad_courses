#ifndef NAMED_NODE_MAP_H
#define NAMED_NODE_MAP_H

#include <string>

#include "NodeList.hpp"

namespace dom {
class Document;

class NamedNodeMap : public NodeList {
public:
    virtual Node* getNamedItem(const std::string&) {
        return 0;
    }
    virtual Node* setNamedItem(Node*) {
        return 0;
    }
    virtual Node* removeNamedItem(const std::string&) {
        return 0;
    }
};
}; // namespace dom

class NamedNodeMap_Impl : public virtual dom::NamedNodeMap {
private:
    dom::Document* document;

public:
    NamedNodeMap_Impl(dom::Document*);

    virtual ~NamedNodeMap_Impl();

    virtual dom::Node* getNamedItem(const std::string&);
    virtual dom::Node* setNamedItem(dom::Node*);
    virtual dom::Node* removeNamedItem(const std::string&);
};

#endif // NAMEDNODEMAP_H
