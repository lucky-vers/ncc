#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cctype>
#include <unordered_set>

using namespace std;

enum class TokenType {
    IDENTIFIER,
    DIGIT,
    KEYWORD,
    OPERATOR,
    SEMICOLON,
    ENDOFFILE,
    CLOSEPAREN,
    OPENPAREN,
};

struct Token {
    TokenType type;
    string value;
};

const unordered_set<string> keywords = {"if", "else", "while", "return", "int", "void"};

vector<Token> tokenize(const string &source) {
    vector<Token> tokens;
    size_t i = 0;
    while (i < source.size()) {
        char c = source[i];
        if (isspace(c)) {
            i++;
            continue;
        }

        if (isalpha(c)) {
            size_t start = i;
            while (i < source.size() && (isalnum(source[i]) || source[i] == '_')) {
                i++;
            }
            string value = source.substr(start, i - start);
            if (keywords.count(value)) {
                tokens.push_back({TokenType::KEYWORD, value});
            } else {
                tokens.push_back({TokenType::IDENTIFIER, value});
            }
        } else if (isdigit(c)) {
            size_t start = i;
            while (i < source.size() && isdigit(source[i])) {
                i++;
            }
            string value = source.substr(start, i - start);
            tokens.push_back({TokenType::DIGIT, value});
        } else if (c == ';') {
            tokens.push_back({TokenType::SEMICOLON, string(1, c)});
            i++;
        } else if (c == '(') {
            tokens.push_back({TokenType::OPENPAREN, string(1, c)});
            i++;
        } else if (c == ')') {
            tokens.push_back({TokenType::CLOSEPAREN, string(1, c)});
            i++;
        } else if (ispunct(c)) {
            tokens.push_back({TokenType::OPERATOR, string(1, c)});
            i++;
        } else {
            cerr << "Unknown character: " << c << endl;
            i++;
        }
    }
    tokens.push_back({TokenType::ENDOFFILE, ""});
    return tokens;
}

void printTokens(const vector<Token> &tokens) {
    for (const Token &token : tokens) {
        cout << "Token(Type: ";
        switch (token.type) {
            case TokenType::IDENTIFIER:
                cout << "IDENTIFIER";
                break;
            case TokenType::DIGIT:
                cout << "DIGIT";
                break;
            case TokenType::KEYWORD:
                cout << "KEYWORD";
                break;
            case TokenType::OPERATOR:
                cout << "OPERATOR";
                break;
            case TokenType::SEMICOLON:
                cout << "SEMICOLON";
                break;
            case TokenType::ENDOFFILE:
                cout << "ENDOFFILE";
                break;
            case TokenType::CLOSEPAREN:
                cout << "CLOSEPAREN";
                break;
            case TokenType::OPENPAREN:
                cout << "OPENPAREN";
                break;
        }
        cout << ", Value: " << "\"" << token.value << "\")" << endl;
    }
}

int main(int argc, char **argv) {
    if (argc == 1) {
        cerr << "Usage: ncc <file>" << endl;
        return 1;
    }

    ifstream input_file(argv[1]);
    if (!input_file.is_open()) {
        cerr << "Error opening the file!" << endl;
        return 1;
    }

    stringstream buf;
    buf << input_file.rdbuf();
    string source_file_contents = buf.str();
    input_file.close();

    vector<Token> tokens = tokenize(source_file_contents);
    printTokens(tokens);

    return 0;
}

