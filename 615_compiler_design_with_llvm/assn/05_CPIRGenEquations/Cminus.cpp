#include "CminusBaseVisitor.h"
#include "CminusLexer.h"
#include "CminusParser.h"
#include "IR_Gen.h"

#include "antlr4-runtime.h"

#include <fstream>
#include <iostream>
#include <string>
#include <strstream>

int main(int argc, char* argv[]) {

    std::ifstream stream;
    stream.open(argv[1]);

    antlr4::ANTLRInputStream input(stream);
    CminusLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    CminusParser parser(&tokens);

    antlr4::tree::ParseTree* tree = parser.program();
    auto lol = CminusBaseVisitor().visit(tree);
    std::cout << tree->toStringTree() << std::endl;
    std::ofstream fd;
    fd.open("C-Output-0-Symbol-Table.txt");
    fd << parser.semantics.dump();
    fd.close();

    return 0;
}