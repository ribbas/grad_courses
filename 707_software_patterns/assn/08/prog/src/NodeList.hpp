#ifndef NODE_LIST_HPP
#define NODE_LIST_HPP

#include <list>

namespace dom {
class Node;

class NodeList : public std::list<Node*> {
public:
    virtual iterator find(Node* n) {
        iterator i;

        for (i = begin(); i != end(); i++) {
            if (*i.operator->() == n) {
                break;
            }
        }

        return i;
    }
};
}; // namespace dom

#endif // NODE_LIST_HPP
