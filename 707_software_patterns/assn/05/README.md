# Assignment 5

The assignment asked for the implementation of the following patterns to the program:

- singleton
- proxy

## Source Files

A combination of the original implementation, my implementation of Assignment 3 and the solution to the last assignment implementation were used. `Test.cpp` has been modified to add command line options for the Iterator and Builder patterns.

To compile the assignment, the updated CMakeLists.txt file can be used.

## Modifications for Assignment

### Singleton

For this pattern, `XMLBuilder` had its constructor made private and only accessible indirectly through its new method `XMLBuilder* getInstance()` which maintains a static variable. This approach ensures no other classes or clients can instantiate more than one copy of the class.

### Proxy

For this pattern, the `ElementProxy` class was added. The class wrapped all of the methods, including constructors and destructors, of `Element`. Most of the methods are implemented as simple pass-throughs. But some methods, especially those that need access to an instantiated `Element`'s children, check if the real subject was implemented before calling its method. If the real object was not realized, it becomes instantiated by the proxy and its flag is set to true.

The proxy is intended to be used by the tokenizer to pause parsing until the real subject needed to be realized. For this pausing behavior, `offset` was added as an attribute to `XMLTokenizer`. This integer variable, initialized to 0, determined where in the file to begin tokenizing. The builder would use the tokenizer to parse the XML file until an Element, where it saves the offset to the proxy. Once the builder determines that the proxy needs to be realized, it resumes tokenizing from the saved offset. Unfortunately, this portion of the algorithm was not fully implemented.
