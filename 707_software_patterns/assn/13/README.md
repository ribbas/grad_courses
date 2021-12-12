# Assignment 13

The assignment asked for the implementation of the following patterns to the program:

- flyweight
- interpreter
- facade

## Source Files

A combination of the original implementation and my implementation of Assignment 9 were used for this assignment.

To compile the assignment, the updated CMakeLists.txt file can be used.

## Modifications for Assignment

### Flyweight

For this pattern, the `Flyweight` and `FlyweightFactory` classes were added. The intrinsic states of the Node class are `<std::string> name`, `<std::string> value`, `<short> nodeType`, and `<Document*> document` and they are moved into the `Flyweight` class. The shared states are stored in the class variable, `nodeFlyweights` which is an `unordered_map` with `std::string` keys and class pointers as the values. The `Flyweight` objects are generated in the Node constructor by passing in the intrinsic states. The factory class implements a single static method that attempts to find a Flyweight object in its unordered map and creates a new pair if it is not found. The method is used by Node objects that need to retrieve the stored intrinsic states.

### Interpreter

For this pattern, The `XMLInterpreter` class was added. The class implements a simple CompoundExpression that parses `Element` objects as Context and extracts the literals and operations. The TerminalExpressions are stored in a stack that gets evaluated into the final result in a loop. The class is used by the newly added `Facade` class that generates an iterator from a Document object to interpret the entire Context. Once the Document is finished iterating, the `eval()` method is called.

### Facade

For this pattern, the `Facade` class was added. The class encapsulates several of the subsystems in the XML framework assignment, including: `XMLBuilder`, `XMLDirector`, `XMLInterpreter`, `XMLSerializer`, `XMLTokenizer` and `XMLValidator`. The class provides a method to generate a `Document` object using the `parse()` method to abstract away the multi-step process from the Client. It also provides the Client the option to set an instantiated `Document` object. Other methods include serialization, tokenization, iterating through the `Document` object, and expression evaluation.
