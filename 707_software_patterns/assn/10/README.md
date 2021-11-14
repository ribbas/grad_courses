# Assignment 10

## Architectural patterns

For an XML file display and editing application, the layers architectural pattern can be applied. The following list will provide descriptions for each of the layers for the program. The layers are listed in the order of the flow of communication, from top to bottom:

- Layer 4: the presentation layer, which consists of the graphical user interface (GUI). This layer ensures all the implementation details are abstracted away from the user and replaced with graphical components. The GUI allows the user to load and open XML files to modify and save them back on disk.
- Layer 3: the business layer, which consists of the immediate interfaces between the GUI and the rest of the program. This layer manages the user request queues and ensures the API of the core program is mapped properly with the GUI.
- Layer 2: the persistence layer, which is an in-memory representation of the XML framework along with all its functionality as implemented in the assignment.
- Layer 1: the database layer, which manages file and database paths and permissions, reading and writing, etc.

## Antipatterns

Some easy patterns to pick from the list would be "OverUseOfPatterns" which suggests the forceful implementation of patterns where it is not necessarily appropriate, or "ReinventTheWheel" which recommends not implementing a program that has already been finalized in a library or package by others. However, both of those antipatterns will deem the intent of the assignments invalid.

One appropriate antipattern that can be found in the assignment is ["IfItIsWorkingDontChange"](http://wiki.c2.com/?IfItIsWorkingDontChange). Although more of a code smell if applied to the assignment at its current state, the antipattern is defined as the belief that if a project is fully functional but using a method that was not preferred, it should be changed. The class that this antipattern can be applied to is `XMLTokenizer`. Almost all of the patterns we were asked to implement in the weekly assignments did not involve modifying that class. Although the class appears to function as intended, the lack of any personal modifications to it provokes a sense of uneasiness. In the framework, it is the only class that utilizes an external library `<boost/regex.hpp>`. The antipattern points out that the developer may believe the code portion can be left unmodified if they were certain that it would never change. However, in the real world, that is almost never the case. The external dependency may cause some issues in the later versions. It may have been beneficial to replace the Boost library with `std::regex`, or manually implement the regular expression functions. Parsing the files with regular expressions may also not have been the appropriate approach, as suggested by another antipattern ["ParsingHtmlWithRegex"](http://wiki.c2.com/?ParsingHtmlWithRegex). This antipattern postulates that using regular expressions to parse HTML, which has similar structures and constraints as XML, may not be viable due to malformed content, etc.

One way to avoid this potential antipattern is to refactor the class and inspect its external dependencies for any possible deprecations in future versions. The next steps would involve replacing the dependency with a library that is considered more stable, or replace the current parsing algorithms altogether.
