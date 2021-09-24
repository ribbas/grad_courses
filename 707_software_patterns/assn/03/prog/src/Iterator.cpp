#include "Iterator.hpp"
#include "Node.hpp"

DOMIterator::DOMIterator(dom::Node* startWithNode) : firstNode(startWithNode) {
    if (firstNode != 0) {
        for (dom::Node* node = firstNode; node->getChildNodes()->size() > 0;
             node = *node->getChildNodes()->begin()) {
            listStack.push(node->getChildNodes());
            indexStack.push(0);
        }
    }
}

dom::Node* DOMIterator::elementAt(dom::NodeList* currentList,
                                  int currentIndex) {
    int i;
    dom::NodeList::iterator it;

    for (i = 0, it = currentList->begin();
         it != currentList->end() && i < currentIndex; i++, it++)
        ;

    return *it;
}

bool DOMIterator::hasNext() {
    return firstNode != 0;
}

dom::Node* DOMIterator::next() {
    dom::NodeList* currentList = listStack.size() > 0 ? listStack.top() : 0;

    if (currentList == 0) {
        dom::Node* temp = firstNode;
        firstNode = 0;
        return temp;
    } else {
        int currentIndex = indexStack.top();
        indexStack.pop();
        dom::Node* temp = elementAt(currentList, currentIndex++);

        if (currentIndex >= currentList->size())
            listStack.pop();
        else {
            indexStack.push(currentIndex);

            for (dom::Node* node = elementAt(currentList, currentIndex);
                 node->getChildNodes()->size() > 0;
                 node = *node->getChildNodes()->begin()) {
                listStack.push(node->getChildNodes());
                indexStack.push(0);
            }
        }

        return temp;
    }
}