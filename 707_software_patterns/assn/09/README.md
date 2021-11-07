# Assignment 9

The assignment asked for the implementation of the following patterns to the program:

- chain of responsibility
- memento

## Source Files

A combination of the original implementation and my implementation of Assignment 6 were used. The test driver was split into separate files to make modifications more convenient.

To compile the assignment, the updated CMakeLists.txt file can be used.

## Modifications for Assignment

### Chain of Responsibility

For this pattern, the `Event` struct and only one method, `bool Element::handleEvent(Event*)`, were added. The `Event` class is currently a simple wrapper for a public string attribute. The struct is processed by the `handleEvent` method, which simply compares the attributes of each of the Element objects to the requested Event, and prints to stdout if it is found. If not, the parent Element calls its method to handle the event until it is either found and printed out to stdout or a message about the Event not being found is displayed. A driver function has been added to test the capabilities of the pattern by sending hard-coded `Event` objects and checking to see if the DOM tree can handle them with its iterator.

### Memento

For this pattern, the private nested `Memento` class was added to `XMLValidator`. It is maintained by its enclosing class which contains them in a stack. `XMLValidator` acts as both the Originator and Caretaker of the Memento. The wide interface is implemented by the private methods that performs the copying, creation and setting of the mementos while the narrow, public interface is implemented with the `save()` and `undo()` methods. These public methods provide wrappers to the Originator methods and interact with the stack to simulate a history of the `XMLValidator`. The existing driver function for the validator was updated to test the capabilities of the pattern by adding another valid attribute after calling `save()`, then reverting to the previous state and testing its validity.
