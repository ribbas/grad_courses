# Assignment 7

The assignment asked for the implementation of one of the following patterns to the program:

- adapter
- bridge

## Source Files

A combination of the original implementation and my implementation of Assignment 6 were used.

`DocumentAdapter.cpp` and `NodeAdapter.cpp` were added to the sources in the CMakeLists. To compile the assignment, the updated CMakeLists.txt file can be used.

## Modifications for Assignment

### Adapter/Bridge

For my solution to the assignment, I applied the adapter pattern instead of the bridge pattern to wrap the DOM classes for their corresponding XERCES classes. Two adapter classes, `NodeAdapter` and `DocumentAdapter`, were added as composition variants of the adapter patterns. The adapter classes were implemented as extensions to the XERCES namespace. All the methods declared in the `DOMNode` and `DOMDocument` header files were declared in the corresponding adapter classes with identical function names and signatures, i.e. `const XMLCh* NodeAdapter::getNodeValue() const` was declared to reflect `const XMLCh* DOMNode::getNodeValue() const`. However, only some of the methods that had been declared and implemented in the corresponding adaptee classes (`Node_Impl` and `Document_Impl`) were implemented properly in the adapter classes. The remaining methods were implemented as empty functions with default behaviors.

My reason for choosing the adapter pattern over the bridge was due to it being more practical to implement the assignment prompt. The bridge pattern would have been used to design a single, common interface to be implemented by both of the `DOMNode` and `DOMDocument` classes and their counterpart DOM classes. In this assignment, the XERCES classes were asked to wrap their corresponding DOM classes. This can be achieved simply with one-to-one adapter classes instead of creating a complex hierarchy of interfaces required by the bridge pattern. Furthermore, adding adapter classes does not require any modification to the XERCES classes. In a bridge pattern, `DOMNode` and `DOMDocument` would have to inherit the general implementation interface.
