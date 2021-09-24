#ifndef ITERATOR_H
#define ITERATOR_H

#include "NodeList.hpp"
#include <stack>

namespace dom {
class Node;

class Iterator {
public:
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

    friend class Document_Impl;

    DOMIterator(dom::Node* startWithNode, Document_Impl* document);
    dom::Node* elementAt(dom::NodeList* currentList, int currentIndex);

public:
    virtual bool hasNext();
    virtual dom::Node* next();
};

#endif