# Assignment 8

The assignment asked for the implementation of the following patterns to the program:

- mediator
- observer

## Source Files

A combination of the original implementation and my implementation of Assignment 6 were used. `Observer` and `Subject` classes were added to the source files.

To compile the assignment, the updated CMakeLists.txt file can be used.

## Modifications for Assignment

### Observer/Mediator

The `Subject` and `Observer` classes implement their corresponding abstract classes. `XMLBuilder` takes the role of the ConcreteSubject class with `XMLValidator` as the ConcreteObserver. The `notify()` method simply loops through all the Observer classes and calls their `update()` methods. The `XMLBuilder.notify()` method is called whenever the class adds a new Element, Attr or Text nodes to the DOM. The `XMLValidator.update()` method gets a reference to the last Element added by `XMLBuilder` and validates it. This validation is implemented through the `ValidChildren` class, with `XMLValidator` being its ConcreteMediator. The Mediator updates all its `ValidChildren` of the validation status. At its current state, the `ValidChildren.getValidationStatus()` method simply repeats the actions of the Mediator by printing to stdout the name and status of the last Element added.
