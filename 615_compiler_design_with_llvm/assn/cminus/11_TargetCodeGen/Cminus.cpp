#include "CminusBaseVisitor.h"
#include "CminusLexer.h"
#include "CminusParser.h"
#include "LLVM_Util.h"

// open a new context and module
std::unique_ptr<llvm::LLVMContext> irContext =
    std::make_unique<llvm::LLVMContext>();

// create a new builder for the module
std::unique_ptr<llvm::IRBuilder<>> irBuilder =
    std::make_unique<llvm::IRBuilder<>>(*irContext);

int main(int argc, char* argv[]) {

    std::ifstream ifs;
    std::string pathName = argv[1];
    ifs.open(pathName);
    size_t pos = pathName.find_last_of("\\/");
    std::string exeName = pathName.erase(0, pos + 1);
    std::string fileName = exeName.substr(0, exeName.length() - 4);

    if (argc == 2) {
        if (!ifs.is_open()) {
            std::cout << "ERROR: Input file " << argv[1] << " not found."
                      << std::endl;
            return 1;
        }
    }

    antlr4::ANTLRInputStream input(ifs);
    CminusLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    CminusParser parser(&tokens);
    CminusBaseVisitor visitor = CminusBaseVisitor(exeName);

    visitor.visit(parser.program());

    std::ofstream fd;
    fd.open(fileName + "-opt.ll");
    visitor.optimize();
    visitor.printModule(fd);
    fd.close();

    visitor.generateObject(fileName + ".o");

    fd.open(fileName + ".sym");
    fd << visitor.semantics.dump();
    fd.close();

    llvm::llvm_shutdown();

    return 0;
}
