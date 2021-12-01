# Assignment 12

The assignment asked for the implementation of the following patterns to the program:

- state
- visitor

## Source Files

A combination of the original implementation and my implementation of Assignment 9 were used for this assignment.

To compile the assignment, the updated CMakeLists.txt file can be used.

## Modifications for Assignment

### State

For this pattern, the `XMLDirector::State` struct was implemented. `XMLDirector` acts as the ConcreteContext for the derived structs of `XMLDirector::State`, which act as the ConcreteStates. The `void XMLDirector::construct()` method was modified to run the finite state machine of the ConcreteStates instead of calling the `XMLBuilder` methods. Each of the ConcreteMethods are responsible for calling combinations of `XMLBuilder` methods to properly implement the Director pattern.

### Visitor

For this pattern, the AbstractVisitor `XMLVisitor` was added. A virtual method was added for every ConcreteElement classes: `Node`, `Document`, `Element`, `Attr`, and `Text`. The previously implemented Strategy pattern method `void serialize(fstream*, WhiteSpaceStrategy*)` was replaced with `void accept(XMLVisitor*)` in the ConcreteElements. To circumvent issues with cyclic dependencies, the AbstractVisitor was left unimplemented to act as an interface to be imported by the ConcreteElements. All of its methods were implemented by the ConcreteVisitor,`XMLSerializer`.
