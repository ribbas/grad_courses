# Assignment 10

## Architectural patterns

For an XML file display and editing application, the layers architectural pattern can be applied. The following list will provide descriptions for each of the layers for the program. The layers are listed in the order of the flow of communication, from top to bottom:

- Layer 4: the presentation layer, which consists of the graphical user interface (GUI). This layer ensures all the implementation details are abstracted away from the user and replaced with graphical components. The GUI allows the user to load and open XML files to modify and save them back on disk.
- Layer 3: the business layer, which consists of the immediate interfaces between the GUI and the rest of the program. This layer manages the user request queues and ensures the API of the core program is mapped properly with the GUI.
- Layer 2: the persistence layer, which is an in-memory representation of the XML framework along with all its functionality as implemented in the assignment.
- Layer 1: the database layer, which manages file and database paths and permissions, reading and writing, etc.

## Antipatterns
