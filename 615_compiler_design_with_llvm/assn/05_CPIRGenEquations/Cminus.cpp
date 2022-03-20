#include "CminusBaseVisitor.h"
#include "CminusLexer.h"
#include "CminusParser.h"
#include "IR_Gen.h"

#include "antlr4-runtime.h"

#include <fstream>
#include <iostream>
#include <string>

#include "IR_Gen.h"

// open a new context and module
std::unique_ptr<llvm::LLVMContext> irContext =
    std::make_unique<llvm::LLVMContext>();

// create a new builder for the module
std::unique_ptr<llvm::IRBuilder<>> irBuilder =
    std::make_unique<llvm::IRBuilder<>>(*irContext);

int main(int argc, char* argv[]) {

    std::ifstream stream;
    std::string pathName = argv[1];
    stream.open(pathName);
    size_t pos = pathName.find_last_of("\\/");
    std::string exeName = pathName.erase(0, pos + 1);

    antlr4::ANTLRInputStream input(stream);
    CminusLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    CminusParser parser(&tokens);

    antlr4::tree::ParseTree* tree = parser.program();

    CminusBaseVisitor visitor = CminusBaseVisitor(exeName);
    visitor.visit(tree);
    visitor.printModule();

    // std::cout << tree->toStringTree() << std::endl;
    std::ofstream fd;
    fd.open("C-Output-0-Symbol-Table.txt");
    fd << visitor.semantics.dump();
    fd.close();
    llvm::llvm_shutdown();

    return 0;
}
