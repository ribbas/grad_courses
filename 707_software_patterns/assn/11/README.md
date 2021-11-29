# Assignment 11

The assignment asked for the implementation of the following patterns to the program:

- command
- prototype

## Source Files

A combination of the original implementation and my implementation of Assignment 9 were used.

To compile the assignment, the updated CMakeLists.txt file can be used.

## Modifications for Assignment

### Command

For this pattern, the `Invoker` and `Command` classes were implemented. The ConcreteCommand subclasses, `ParseFileCommand`, `SerializeCommand`, `AddAttributeCommand`, and `IterateToStdoutCommand` were also implemented. The `Invoker` class maintains 2 separate queues to manage the ConcreteCommand classes and their corresponding arguments. Once the queues are filled, the `run()` method can be executed to invoke them one after the other. The public `dom::Document* Invoker::document` attribute acts as the Receiver for the Commands. The attribute is used by all the ConcreteCommands in their corresponding commands.

### Prototype

For this pattern, only the `dom::Node* clone()` method was added to all of the DOM classes, `Node`, `Element`, `Document`, `Text`, and `Attr`. For the `Node` and `Document` classes, the default behavior is implemented due to making copies of them not being appropriate to the prompt and scope of the assignment. The `Text` and `Attr` classes return new instances of themselves using identical attribute values. The `Element` class follows the same behavior along with copying its children nodes and attributes to implement a deep copy of the DOM tree.
