#include "Test.hpp"

void testCommand(int argc, char** argv) {

    if (argc < 2) {
        printUsage();
        exit(0);
    }

    XMLInvoker invoker;

    std::string arg1 = argv[2];
    std::string arg2 = argv[3];

    invoker.addCommand(new ParseFileCommand(&invoker), arg1);
    invoker.addCommand(new AddAttributeCommand(&invoker),
                       "attribute;new value");
    invoker.addCommand(new SerializeCommand(&invoker), arg2);
    invoker.addCommand(new IterateToStdoutCommand(&invoker));

    invoker.run();
}
