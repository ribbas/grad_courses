#ifndef ITERATOR_H
#define ITERATOR_H

#include "Node.hpp"
#include <vector>

namespace dom {
class Node;

class Iterator {
private:
    virtual void containerize(Node*, bool) = 0;

public:
    virtual ~Iterator() {}

    virtual void next() = 0;
    virtual void first() = 0;
    virtual bool isDone() = 0;
    virtual Node* currentItem() = 0;
};
} // namespace dom

class Document_Impl;
class XMLIterator : public virtual dom::Iterator {

private:
    friend class Document_Impl;

    std::vector<dom::Node*> container;
    std::vector<dom::Node*>::iterator it;
    int index;

    XMLIterator(dom::Document*);
    virtual void containerize(dom::Node*, bool = true);

public:
    virtual void next();
    virtual void first();
    virtual bool isDone();
    virtual dom::Node* currentItem();
};

#endif
