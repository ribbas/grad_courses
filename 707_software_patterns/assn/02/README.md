# Assignment 2

The assignment asked for the implementation of the following patterns to the program:

- factory
- strategy
- decorator

The factory pattern was not implemented properly in my assignment. The `DocumentNodeFactory` class was meant to create an indirection between `Document` and all the `Node` type DOM classes it instantiates (`Element`, `Attr`, `Text`). Although it decouples the classes, the class does not contain all the attributes required for a Concrete Creator of the factory method.

The strategy pattern was applied to the various algorithms in `XMLSerialization`. Two separate but tightly coupled Contexts have been added, `XMLSerializationContext` and `DOMSerializationContext`. `XMLSerializationContext` implements two strategies, `XMLSerializationPretty` and `XMLSerializationMinimal`. `DOMSerializationContext` implements four strategies, each for the subclasses of `Node`: `DocumentSerialization`, `ElementSerialization`, `AttrSerialization` and `TextSerialization`. The `XMLSerializationContext` strategies compose of `DOMSerializationContext` strategies and invokes a combination of 8 possible strategies.

Decorators were not implemented properly in my assignment. The `XMLValidator` class was meant to serve as an interface for the Concrete Components, `ElementComponent`, `AttrComponent` and `TextComponent`. Each of these Concrete Decorators were supposed to Decorate their corresponding existing DOM classes (`Element`, `Attr` and `Text`) by extending a `validate()` method to them. Although these subclasses move the validation checks from the base `XMLValidator` to the Concrete Decorators, the subclasses were not implemented properly since they accept the DOM objects as an argument in their methods instead of their constructors.

To compile the assignment, the CMakeLists.txt file can be used.
