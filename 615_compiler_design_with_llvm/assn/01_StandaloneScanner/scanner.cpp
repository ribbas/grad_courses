/**
 * 605.615 Homework 1: Scanner
 * Sabbir Ahmed
 *
 * This file consists of the functions required to read in a file and tokenize
 * its contents. The tokens are categorized into Keyword, Whitespace, Symbol,
 * Identifier, and Number. The file also contains provides the functionalities
 * to print the tokens and their corresponding statistics and clean up
 * afterwards.
 */

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::string token_type_str[5] = {"KW", "WS", "SYM", "ID", "NUM"};
typedef enum { KW, WS, SYM, ID, NUM } token_type;

struct Token {
    std::string name;
    token_type type;
    std::string to_string() {
        return "(\"" + name + "\", " + token_type_str[type] + ")";
    }
};

unsigned int LOGICAL_COUNT = 0;
unsigned int CHAR_CMP_COUNT = 0;

/**
 * Read content of file line by line into a string
 */
std::string read_file(std::fstream& file) {

    std::string temp, line;

    std::getline(file, temp);
    line = temp;
    while (temp.size()) {
        std::getline(file, temp);
        line += temp;
    }
    return line;
}

/**
 * Convert Token name to lowercase to make string comparisons
 * case-insensitive
 */
std::string to_lower_case(std::string token_name) {

    std::string lower = token_name;
    for (unsigned int i = 0; i < lower.length(); i++) {

        // +1 for the for-loop
        // +1 for the char comparison
        CHAR_CMP_COUNT += 2;
        if ((lower[i] >= 'A') && (lower[i] <= 'Z')) {
            lower[i] += ('a' - 'A');
        }
    }

    return lower;
}

/**
 * Determine if Token string is NUM
 */
bool is_numeric_type(std::string token_name) {

    for (unsigned int i = 0; i < token_name.length(); i++) {

        // +1 for the for-loop
        LOGICAL_COUNT++;
        // +10 for the char comparisons
        CHAR_CMP_COUNT += 10;

        switch (token_name[i]) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9': {
                break;
            }

            // if non-numeric character
            default: {
                return false;
            }
        }
    }

    return true;
}

/**
 * Determine if Token string is KW
 */
bool is_keyword_type(std::string token_name) {
    // +19 for the length of the keyword strings
    CHAR_CMP_COUNT += 19;
    return (token_name == "if") || (token_name == "then") ||
           (token_name == "else") || (token_name == "end") ||
           (token_name == "return");
}

/**
 * Update Token type of Tokens that are not WS or SYM
 */
void update_token_type(Token* token) {

    // if token is not WS or SYM
    if ((++LOGICAL_COUNT) && !(token->type == WS) && !(token->type == SYM)) {

        // transform token name to lowercase
        std::string token_name = to_lower_case(token->name);

        // if token is not KW
        if ((++LOGICAL_COUNT) && !is_keyword_type(token_name)) {

            //  if token name is numeric
            if ((++LOGICAL_COUNT) && is_numeric_type(token_name)) {

                token->type = NUM;

            } else {

                token->type = ID;
            }
        }
    }
}

/**
 * Tokenize file content string and store them into a vector
 */
void tokenize(std::string contents, std::vector<Token*>* tokens) {

    unsigned int cursor = 0;
    Token* token = new Token;

    // loop through the content string
    while ((++LOGICAL_COUNT) && cursor < contents.length()) {

        // +9 for char comparison
        CHAR_CMP_COUNT += 9;

        // compare char, where WS or SYM are considered delimiters
        switch (contents[cursor]) {

            // if char is WS or SYM
            case ' ':
            case '\t':
            case '\r':
            case '\n':
            case '(':
            case ')':
            case '=':
            case '+':
            case ';': {

                // if token was initialized, append to vector of tokens with
                // default type of KW
                if (token->name.length()) {
                    token->type = KW;
                    tokens->push_back(token);
                } else {
                    delete token;
                }
                token = new Token;

                // +9 for char comparison
                CHAR_CMP_COUNT += 9;
                switch (contents[cursor]) {

                    case ' ': {

                        // assign name of token to '\s'
                        token->name = "\\s";
                        // assign type of token to SYM
                        token->type = WS;
                        break;
                    };

                    case '\t': {

                        // assign name of token to '\t'
                        token->name = "\\t";
                        // assign type of token to SYM
                        token->type = WS;
                        break;
                    };

                    case '\n':
                    case '\r': {

                        // assign name of token to '\n'
                        token->name = "\\n";
                        // assign type of token to SYM
                        token->type = WS;
                        break;
                    };

                    // if char is any of the SYM characters
                    case '(':
                    case ')':
                    case '=':
                    case '+':
                    case ';': {

                        // assign name of token to the char
                        token->name = contents[cursor];
                        // assign type of token to SYM
                        token->type = SYM;
                        break;
                    }

                    // should not reach here
                    default: {
                        break;
                    }
                }

                tokens->push_back(token);
                token = new Token;

                break;
            }

            // else, keep appending the token string
            default: {
                token->name += contents[cursor];
                break;
            }
        }

        // increment cursor
        cursor++;
    }

    // if an extra token was created
    if (!token->name.length()) {
        delete token;
        token = nullptr;
    }
}

/**
 * Print Token attributes and statistics from the vector of Tokens
 */
void print_tokens(std::vector<Token*>* tokens) {

    unsigned int KW_count = 0;
    unsigned int WS_count = 0;
    unsigned int SYM_count = 0;
    unsigned int ID_count = 0;
    unsigned int NUM_count = 0;
    for (unsigned int i = 0; i < tokens->size(); i++) {

        std::cout << (*tokens)[i]->to_string();

        // generate statistics on token types
        if ((*tokens)[i]->type == KW) {
            KW_count++;
        } else if ((*tokens)[i]->type == WS) {
            WS_count++;
        } else if ((*tokens)[i]->type == SYM) {
            SYM_count++;
        } else if ((*tokens)[i]->type == ID) {
            ID_count++;
        } else if ((*tokens)[i]->type == NUM) {
            NUM_count++;
        }

        if (i < tokens->size() - 1) {
            std::cout << ',';
        } else {
            std::cout << '\n';
        }
    }

    std::cout << '\n';
    std::cout << "Logical count: " << LOGICAL_COUNT << '\n';
    std::cout << "Char comparison count: " << CHAR_CMP_COUNT << '\n';
    std::cout << '\n';
    std::cout << "Total tokens: " << tokens->size() << '\n';
    std::cout << "KW count: " << KW_count << '\n';
    std::cout << "WS count: " << WS_count << '\n';
    std::cout << "SYM count: " << SYM_count << '\n';
    std::cout << "ID count: " << ID_count << '\n';
    std::cout << "NUM count: " << NUM_count << '\n';
}

int main(int, char** argv) {

    // read in file provided as an argument
    std::fstream file = std::fstream(argv[1], std::fstream::in);
    std::string contents = read_file(file);

    // print the contents of the file
    std::cout << contents << '\n';

    // initialize an empty vector of Tokens
    std::vector<Token*>* tokens = new std::vector<Token*>;

    // tokenize file content into the vector
    tokenize(contents, tokens);
    for (unsigned int i = 0; i < tokens->size(); i++) {
        update_token_type((*tokens)[i]);
    }

    // print the vector of tokens
    print_tokens(tokens);

    // clean up
    for (unsigned int i = 0; i < tokens->size(); i++) {
        delete (*tokens)[i];
        (*tokens)[i] = nullptr;
    }
    delete tokens;
    tokens = nullptr;

    file.close();
}
