# Assignment 7

The assignment asked for the implementation of the following patterns to the program:

- adapter
- bridge

## Source Files

A combination of the original implementation and my implementation of Assignment 6 were used.

`DocumentAdapter.cpp` and `NodeAdapter.cpp` were added to the sources in the CMakeLists. To compile the assignment, the updated CMakeLists.txt file can be used.

## Modifications for Assignment

### Adapter/Bridge

For my solution to the assignment, I applied the adapter pattern instead of the bridge pattern to wrap the DOM classes for the corresponding XERCES classes. Two adapter classes, `NodeAdapter` and `DocumentAdapter`, were added as composition variants of the adapter patterns.
