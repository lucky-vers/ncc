#pragma once

#include <sstream>
#include <vector>
#include <cctype>
#include <unordered_set>

using namespace std;

enum class TokenType {
};

struct Token {
    TokenType type;
    string value;
};

const unordered_set<string> keywords = {"if", "else", "while", "return", "int", "void"};

enum class TokenKeywords {
};

vector<Token> tokenize(const string &source);

void printTokens(const vector<Token> &tokens);

int lexer(string file);
