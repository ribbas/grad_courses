# Assignment 6

The assignment asked for the implementation of the following patterns to the program:

- idioms
- pattern language

## Source Files

A combination of the original implementation, my implementation of Assignment 4.

To compile the assignment, the updated CMakeLists.txt file can be used.

## Modifications for Assignment

### Idioms

Some idioms have already been applied to the implementation before this assignment. For example, virtual constructors have already existed in the DOM hierarchy. The `Node` class is implemented as an abstract class that is derived by the `Document`, `Element`, `Attr` and `Text` subclasses. The `Node` class itself cannot be instantiated. This was expanded upon to implement the [Concrete Data Type](https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Concrete_Data_Type) idiom. The interfaces of the DOM classes were separated from their implementations and their destructors were made protected. This change forced the non-abstract `Node` subclasses to only allocate dynamically. This ensured that objects of these classes were only being allocated on the heap. Furthermore, the destructor of `Document` was modified to destroy all the created nodes properly and all the memory leaks were fixed in the program.

### Pattern language
