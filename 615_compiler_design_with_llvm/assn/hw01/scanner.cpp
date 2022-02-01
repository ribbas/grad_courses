#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

typedef enum { KW, WS, SYM, ID, NUM } token_type;
std::string token_type_str[] = {"KW", "WS", "SYM", "ID", "NUM"};
struct Token {
    std::string name;
    token_type type;
    std::string to_string() {
        return "(\"" + name + "\", " + token_type_str[type] + ")";
    }
};

std::string read_file(std::fstream& file) {

    std::string temp, line;

    std::getline(file, temp);
    line = temp;
    while (temp.size() != 0) {
        std::getline(file, temp);
        line += temp;
    }
    return line;
}

bool is_numeric(std::string token_name) {

    for (unsigned int i = 0; i < token_name.length(); i++) {

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

void update_token_type(Token* token) {

    // if token is not WS or SYM
    if (!(token->type == WS) && !(token->type == SYM)) {

        // if token is not KW
        if (!(std::set<std::string>{"if", "then", "else", "end", "return"})
                 .count(token->name)) {

            //  if token name is numeric
            if (is_numeric(token->name)) {
                token->type = NUM;

            } else {
                token->type = ID;
            }
        }
    }
}

void tokenize(std::string contents, std::vector<Token*>* tokens) {

    Token* token = new Token;
    unsigned int inc = 0;

    while (inc < contents.length()) {

        switch (contents[inc]) {

            case ' ':
            case '\t':
            case '\r':
            case '\n':
            case '(':
            case ')':
            case '=':
            case '+':
            case ';': {

                if (token->name.length()) {
                    token->type = KW;
                    tokens->push_back(token);
                } else {
                    delete token;
                }
                token = new Token;

                switch (contents[inc]) {

                    case ' ': {

                        token->name = "\\s";
                        token->type = WS;
                        break;
                    };

                    case '\t': {

                        token->name = "\\t";
                        token->type = WS;
                        break;
                    };

                    case '\n': {

                        token->name = "\\n";
                        token->type = WS;
                        break;
                    };

                    case '\r': {

                        token->name = "\\r";
                        token->type = WS;
                        break;
                    };

                    case '(':
                    case ')':
                    case '=':
                    case '+':
                    case ';': {

                        token->name = contents[inc];
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

            default: {
                token->name += contents[inc];
                break;
            }
        }

        inc++;
    }

    if (!token->name.length()) {
        delete token;
    }
}

int main(int, char** argv) {
    std::fstream file = std::fstream(argv[1], std::fstream::in);
    std::string contents = read_file(file);
    std::cout << contents << '\n';

    std::vector<Token*>* tokens = new std::vector<Token*>;
    tokenize(contents, tokens);
    for (unsigned int i = 0; i < tokens->size(); i++) {
        update_token_type((*tokens)[i]);
        std::cout << (*tokens)[i]->to_string() << '\n';
    }

    // clean up
    for (unsigned int i = 0; i < tokens->size(); i++) {
        delete (*tokens)[i];
        (*tokens)[i] = nullptr;
    }
    delete tokens;
    tokens = nullptr;

    file.close();
}
