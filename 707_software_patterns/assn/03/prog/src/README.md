# Assignment 3

The assignment asked for the implementation of the following patterns to the program:

- composite
- iterator

## Source Files

A mixture of the original implementation, my last assignment implementation and the solution to the last assignment implementation were used. The Strategy pattern in XMLSerializer was maintained from the last assignment's solution, adding `Whitespace.hpp` to the source.

To compile the assignment, the updated CMakeLists.txt file can be used.

## Modifications for Assignment

### Composite pattern

For the pattern, the Node class was considered a composite class of the leaf classes Attr and Text. Transparency was prioritized, where the leaf classes had access to and overrode the composite class methods that maintained children objects and common methods on them. The methods `insertBefore(Node*, Node*)`, `replaceChild(Node*, Node*)`, `removeChild(Node*)`, and `appendChild(Node*)` are overridden in Attr and Text to throw an exception to the client.

### Iterator patter

For the pattern, an additional class Iterator was added. The Document class is a friend class of Iterator to gain access to its private constructor in `Iterator* Document::createIterator()`. The class recursively gathers all the children nodes of the document, stores it in its internal vector and is exposed as a container iterator to the client to traverse through. The XMLSerializer maintained its Strategy implementation which does not require usage of this iterator. However, it can be possible to replace the recursive approach to the serializations into iterative loops using the Iterator.
