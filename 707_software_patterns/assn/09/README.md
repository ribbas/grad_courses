# Assignment 6

The assignment asked for the implementation of the following patterns to the program:

- idioms
- pattern language

## Source Files

A combination of the original implementation, my implementation of Assignment 4.

To compile the assignment, the updated CMakeLists.txt file can be used.

## Modifications for Assignment

### Idioms

Some idioms have already been applied to the implementation before this assignment. For example, virtual constructors have already existed in the DOM hierarchy. The `Node` class is implemented as an abstract class that is derived by the `Document`, `Element`, `Attr` and `Text` subclasses. The `Node` class itself cannot be instantiated. This was expanded upon to implement the [Concrete Data Type](https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Concrete_Data_Type) idiom. The interfaces of the DOM classes were separated from their implementations and their destructors were made protected. This change forced the non-abstract `Node` subclasses to only allocate dynamically on the heap. Furthermore, the destructor of `Document` was modified to destroy all the created nodes properly and all the memory leaks were fixed in the program.

### Pattern language

The following is a list of patterns from the language that can be used for a user interface for the application:

1. Explorable interface: the core requirements of the interface is that the user should be able to open, view, edit, save and create the XML files. There are several use cases where the user would prefer to interact with the files on varying technical depths depending on their knowledge on the domain. The user may want full control of the XML file they are creating in one instance, while in another may want default settings to apply and create boilerplate XML files.

2. Multiple settings: the user must be able to open, view, edit, save and create the XML files seamlessly without having to halt in any of those steps. Viewing the files while editing or saving them is a basic requirement of modern applications.

3. Command control center: the user must be able to have access to change the interaction option with the XML files at any time. If they are editing a file, they should have access to save it without having to search for it. Since the requirements of the application is to interact with multiple XML files, a command control center is key to easily swap files to interact with. This command control center can be achieved via the addition of a menubar.

4. Garden of windows: the user must be able to apply multiple settings with a command control center on multiple files. Having separate windows for separate files is useful when the user wants to open, view, edit and compare multiple files simultaneously.

5. Modeless feedback area: the user must be able to interact with the XML files seamlessly without distracting interruptions. If they are editing files, but the `XMLValidator` parses their edit and determines that there is an error, the user should not be bombarded with pop up windows. Instead, there can be an area at the bottom of the window to view the status of the file the user is interacting with. The status area can also display if the file is in valid XML format, if it was saved and when and other information. The statuses can also make use of visual symbols, such as a floppy disk to display successful saving of a file, check and cross marks for validity of XML files, numbers displaying the number of files open, etc.
