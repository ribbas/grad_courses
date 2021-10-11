#include "Iterator.hpp"
#include "Node.hpp"
#include <iostream>

DocumentIterator::DocumentIterator(dom::Document* document) {

    containerize((dom::Node*)document);
}

void DocumentIterator::containerize(dom::Node* document, bool init) {

    if (init) {
        container.push_back(document);
    }

    if (document->hasChildNodes()) {
        for (dom::Node* i : *document->getChildNodes()) {

            container.push_back(i);
            if (i->hasChildNodes()) {
                containerize(i, false);
            }
        }
    }
}

void DocumentIterator::first() {
    it = container.begin();
}

bool DocumentIterator::isDone() {
    return it == container.end();
}

dom::Node* DocumentIterator::currentItem() {
    return container[it - container.begin()];
}

void DocumentIterator::next() {
    it++;
}