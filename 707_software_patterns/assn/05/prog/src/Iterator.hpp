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
class DocumentIterator : public virtual dom::Iterator {

private:
    friend class Document_Impl;

    std::vector<dom::Node*> container;
    std::vector<dom::Node*>::iterator it;

    DocumentIterator(dom::Document*);
    virtual void containerize(dom::Node*, bool = true) override;

public:
    virtual void next() override;
    virtual void first() override;
    virtual bool isDone() override;
    virtual dom::Node* currentItem() override;
};

#endif
