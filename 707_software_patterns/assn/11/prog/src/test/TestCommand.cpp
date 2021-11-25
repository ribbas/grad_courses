#include "Test.hpp"

void testCommand(int argc, char** argv) {

    if (argc < 2) {
        printUsage();
        exit(0);
    }

    Invoker invoker;

    invoker.addCommand(new ParseFileCommand(&invoker), argv[2]);
    invoker.addCommand(new SerializeCommand(&invoker), argv[2]);
    // invoker.addCommand(new AddAttributeCommand(&invoker),
    //                    "attribute;attribute value");

    invoker.run();
}
