#include "Test.hpp"

void testBuilder(int argc, char** argv) {

    if (argc < 4) {
        printUsage();
        exit(0);
    }

    XMLBuilder* builder = new XMLBuilder();
    XMLDirector director(builder, argv[2]);
    director.construct();
    dom::Document* builtDocument = director.getResult();

    std::cout << "DOM Tree successfully built\n";

    //
    // Serialize
    //
    std::fstream* file = nullptr;
    XMLSerializer xmlSerializer(
        file = new std::fstream(argv[3], std::ios_base::out));
    xmlSerializer.serializePretty();
    builtDocument->accept(&xmlSerializer);

    delete builtDocument;
    delete builder;
    delete file;
}
