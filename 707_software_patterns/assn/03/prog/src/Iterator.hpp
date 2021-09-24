#ifndef ITERATOR_H
#define ITERATOR_H

#include "Node.hpp"
#include "NodeList.hpp"
#include <stack>

namespace dom {
class Node;

class Iterator {
public:
    virtual ~Iterator() {}

    virtual Node* elementAt(NodeList*, int) = 0;
    virtual bool hasNext() = 0;
    virtual Node* next() = 0;
};
} // namespace dom

class Document_Impl;
class DOMIterator : public virtual dom::Iterator {
private:
    dom::Node* firstNode;
    std::stack<dom::NodeList*> listStack;
    std::stack<int> indexStack;

public:
    friend class Document_Impl;
    DOMIterator(dom::Node*);
    // virtual ~DOMIterator();

    virtual dom::Node* elementAt(dom::NodeList* currentList, int currentIndex);
    virtual bool hasNext();
    virtual dom::Node* next();
};

#endif