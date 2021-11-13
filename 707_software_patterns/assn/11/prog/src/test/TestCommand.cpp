#include "Test.hpp"

void testCommand(int argc, char** argv) {

    if (argc < 2) {
        printUsage();
        exit(0);
    }

    Invoker invoker;

    invoker.addCommand(new ParseFileCommand(argv[2]));
    // invoker.addCommand(new SerializeCommand());
    // invoker.addCommand(new AddAttributeCommand());

    invoker.run();
}
