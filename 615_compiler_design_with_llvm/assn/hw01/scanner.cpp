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
    return token_name.find_first_not_of("0123456789") == std::string::npos;
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

void tokenize(std::string contents) {

    std::vector<Token*> tokens;
    int contents_len = 0;
    Token* token = new Token;

    while (contents_len < contents.length()) {

        switch (contents[contents_len]) {

            case ' ': {

                if (token->name.length()) {
                    token->type = KW;
                    tokens.push_back(token);
                }

                token = new Token;
                token->name = "\\s";
                token->type = WS;
                tokens.push_back(token);
                token = new Token;

                break;
            };

            case '\t': {
                if (token->name.length()) {
                    token->type = KW;
                    tokens.push_back(token);
                }

                token = new Token;
                token->name = "\\t";
                token->type = WS;
                tokens.push_back(token);
                token = new Token;

                break;
            };

            case '\n': {
                if (token->name.length()) {
                    token->type = KW;
                    tokens.push_back(token);
                }

                token = new Token;
                token->name = "\\n";
                token->type = WS;
                tokens.push_back(token);
                token = new Token;

                break;
            };

            case '\r': {
                if (token->name.length()) {
                    token->type = KW;
                    tokens.push_back(token);
                }

                token = new Token;
                token->name = "\\r";
                token->type = WS;
                tokens.push_back(token);
                token = new Token;

                break;
            };

            case '(':
            case ')':
            case '=':
            case '+':
            case ';': {

                if (token->name.length()) {
                    token->type = KW;
                    tokens.push_back(token);
                }

                token = new Token;
                token->name = contents[contents_len];
                token->type = SYM;
                tokens.push_back(token);
                token = new Token;

                break;
            }

            default: {
                token->name += contents[contents_len];
                break;
            }
        }

        contents_len++;
    }

    for (int i = 0; i < tokens.size(); i++) {
        update_token_type(tokens[i]);
        std::cout << tokens[i]->to_string() << '\n';
    }
}

int main(int, char** argv) {
    std::fstream file = std::fstream(argv[1], std::fstream::in);
    std::string contents = read_file(file);
    std::cout << contents << '\n';
    tokenize(contents);
    file.close();
}
