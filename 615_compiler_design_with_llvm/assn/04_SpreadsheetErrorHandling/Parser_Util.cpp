#include "Parser.h"

#include <cstring>

void Parser::updateCursor() {
    cursor += lookahead->getLexeme().length();
}

// scanto(synchset) throws away tokens until
// a synchronizing token is found in the sync_set.
void Parser::scanTo(char*& ch, FF_List synchset) {

    while (!synchset.contains(lookahead->getKind())) {

        TokenKind kind = lookahead->getKind();

        std::cerr << '\t' << equationName << "\n\t";
        for (unsigned int i = 0; i < cursor; i++) {
            std::cerr << ' ';
        }
        std::cerr << '^' << '\n';

        std::cerr << "Panic Mode: Deleting token " << kind;
        if (kind == ID || kind == NUM) {
            std::cerr << ' ' << lookahead->getLexeme() << '\n';
        }
        std::cerr << '\n';

        if (kind == T_EOF) {
            return;
        }
        delete lookahead;
        lookahead = getToken(ch);
        updateCursor();
    }
}

// checkinput(firstset, synchset) verifies that the input token
// matches the state of the parser at the start of a function.
// If not, it produces an error message and calls scanto(synchset).
void Parser::checkInput(char*& ch, FF_List firstset, FF_List synchset) {

    TokenKind kind = lookahead->getKind();
    if (!firstset.contains(kind)) {

        std::cerr << "Error: Unrecognized token " << kind;
        if (kind == ID || kind == NUM) {
            std::cerr << ' ' << lookahead->getLexeme();
        }
        std::cerr << '\n';

        scanTo(ch, (firstset + synchset));
    }
}

// checkfollows(synchset) verifies that the input token
// matches the state of the parser at the end of a function.
// If not, it produces an error message and calls scanto(synchset).
void Parser::checkFollows(char*& ch, FF_List synchset) {

    TokenKind kind = lookahead->getKind();
    if (!synchset.contains(kind)) {

        std::cerr << "Error: Unrecognized token " << kind;
        if (kind == ID || kind == NUM) {
            std::cerr << ' ' << lookahead->getLexeme();
        }
        std::cerr << '\n';

        scanTo(ch, synchset);
    }
}

/*
 * Check if the TokenKind matches without updating lookahead
 */
bool Parser::nextIs(TokenKind expectedToken) {
    return lookahead->getKind() == expectedToken;
}

/*
 * Update lookahead token if the TokenKind matches
 */
Token* Parser::match(char*& ch, TokenKind expected) {

    if (nextIs(expected)) {

        Token* nextToken = lookahead;
        lookahead = getToken(ch);
        updateCursor();

        return nextToken;

    } else {

        std::cerr << "Unexpected token: " << expected << '\n';
        return nullptr;
    }
}

char* Parser::stripWS(char* input) {
    unsigned int i, j;
    char* output = input;
    for (i = 0, j = 0; i < strlen(input); i++, j++) {
        if (ASCII[(int)input[i]]) {
            output[j] = input[i];
        } else {
            j--;
        }
    }
    output[j] = 0;

    return output;
}
