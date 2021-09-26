#include "Iterator.hpp"
#include "Node.hpp"
#include <iostream>

XMLIterator::XMLIterator(dom::Document* document) : index(0) {

    containerize((dom::Node*)document);
}

void XMLIterator::first() {
    it = container.begin();
}

void XMLIterator::containerize(dom::Node* document, bool init) {

    if (init) {
        container.push_back(document);
    }

    if (document->hasChildNodes()) {
        for (auto i : *document->getChildNodes()) {

            container.push_back(i);
            if (i->hasChildNodes()) {
                containerize(i, false);
            }
        }
    }
}

bool XMLIterator::isDone() {
    return it == container.end();
}

dom::Node* XMLIterator::currentItem() {
    return container[index];
}

void XMLIterator::next() {
    it++;
    index++;
}