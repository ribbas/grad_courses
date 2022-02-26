#include "CminusLexer.h"
#include "CminusParser.h"
#include "antlr4-runtime.h"

#include <iostream>
#include <string>
#include <strstream>

class MyParserErrorListener : public antlr4::BaseErrorListener {
    virtual void syntaxError(antlr4::Recognizer* recognizer,
                             antlr4::Token* offendingSymbol, size_t line,
                             size_t charPositionInLine, const std::string& msg,
                             std::exception_ptr e) override {
        std::ostrstream s;
        s << "Line(" << line << ":" << charPositionInLine << ") Error(" << msg
          << ")";
        throw std::invalid_argument(s.str());
    }
};

int main(int argc, char* argv[]) {

    std::ifstream stream;
    stream.open(argv[1]);

    antlr4::ANTLRInputStream input(stream);
    CminusLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    CminusParser parser(&tokens);

    // MyParserErrorListener errorListner;

    tokens.fill();
    // Only if you want to list the tokens
    for (auto token : tokens.getTokens()) {
        std::cout << token->toString() << std::endl;
    }

    // parser.removeErrorListeners();
    // parser.addErrorListener(&errorListner);
    try {
        antlr4::tree::ParseTree* tree = parser.program();
        std::cout << tree->toStringTree() << std::endl;

        return 0;

    } catch (std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
        return 10;
    }
}