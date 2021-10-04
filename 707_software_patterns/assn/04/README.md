# Assignment 4

The assignment asked for the implementation of the following patterns to the program:

- template method
- abstract factory
- builder

## Source Files

A combination of the original implementation, my implementation of Assignment 3 and the solution to the last assignment implementation were used. `Test.cpp` has been modified to add command line options for the Iterator and Builder patterns.

To compile the assignment, the updated CMakeLists.txt file can be used.

## Modifications for Assignment

### Template Method

For this pattern, several methods have been added to all the Node subclasses:

```c++
void appendValue(fstream*, WhitespaceStrategy*);
void prependNodeName(fstream*, WhitespaceStrategy*);
void prependNodeValue(fstream*, WhitespaceStrategy*);
```

to account for the variant portions of the serialization of each strategies. These methods replace their corresponding `serialize()` methods. The serialized method have been moved to the parent class (Node) and it consolidates all the invariant portions of the serialization. Since the original strategized implementation left little room for the template method pattern, several portions of the serialization algorithms were refactored to forced some commonality.

### Abstract Factory

For this pattern, there were no additional classes or methods. The Builder pattern makes use of this pattern through its director class, XMLDirector. The Director class acts as an abstract factory by accepting the Builder class as a parameter.

### Builder

For this pattern, the XMLBuilder and XMLDirector classes were added. The 2 classes are used to parse a valid input XML by tokenizing it and reserializing the file with the tokens. The Builder class provides all the methods necessary to build a DOM tree, and the Director class uses the tokenizer to determine the sequence of the Builder method calls to reconstruct the XML file. The parsing was implemented by utilizing a greedy-approach of the XMLTokenizer by only checking for attributes, texts, elements, and start and end tags. The parser was only tested with the original `Test1.xml`.
