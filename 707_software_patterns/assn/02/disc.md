1. Factory Method

   1. What are the differences between a method that is a factory and the Factory Method pattern?
   2. Are the create functions in the Document interface Factory Methods? Why?
   3. How does Factory Method promote loosely coupled code? In other words, why use a Factory Method instead of a statement like “new MazeRoom;”?
      1. "Any problem in computer science can be solved with another layer of indirection."—David Wheeler (chief programmer for the EDSAC project in the early 1950s)
         1. How does Factory Method introduce indirection?
         2. What problem does the indirection solve?
   4. Does having a parameterized Factory Method eliminate the advantage of hiding the ConcreteCreator?
   5. Who creates the appropriate Factory Method concrete class? How does Factory Method not just push the problem that it is solving back one step?
   6. Factory Methods appear commonly in frameworks because both the framework and its clients need to use each others classes. What are two ways that the Factory Method is used in this context? Where might Factory Methods be used outside of a framework?

2. Strategy

   1. Is XMLTokenizer.XMLToken a Strategy class?

   2. When the book discusses the applicability of Strategy it says that one use is to remove many conditional statements by putting each block in a concrete Strategy.
      1. What conditional statements are removed in the assignment? What kind of conditions are usually considered for this pattern?
      2. How does their removal reduce coupling?
   3. How do you configure the context with the correct Concrete Strategy?
   4. Can a concrete Strategy be shared between different Context objects?

3. Decorator
   1. There are multiple interfaces in the Node type hierarchy, each with an implementation. Is Node the best interface in the hierarchy to Decorate, or would a subordinate interface one work better?
   2. A decorator object’s interface must conform to the object that it decorates. Now consider an object A that is decorated with an object B. Since object B “decorates” object A, object B shares an interface with object A. If some client is then passed an instance of this decorated object, and that method attempts to call a method on B that is not part of A’s interface, does this mean that the object is no longer a Decorator in the strict sense of the pattern? Furthermore why is it important that a decorator object’s interface conforms to the interface of the component that it decorates?
   3. What further requirement is there on Decorators (and Proxies and Strategies) than just conforming to the interface in order to make them work in place of the original object? Remember that there are more things that should be specified about a method on an interface than just its signature.
   4. Who decorates objects? The main or test function in my implementation of XMLValidator needs to explicitly construct decorated objects. What other pattern-based refinement can we add to the implementation to minimize this and make the Decorator version of validation look almost like the XMLSerializer test?
   5. How is the exercise implementation of Schema/DTD validation different from a traditional implementation? (The implementation provided with the framework is traditional.) Is this good or bad?
