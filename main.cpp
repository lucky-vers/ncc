#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cctype>

#include "lexer.hpp"

using namespace std;

int main(int argc, char **argv) {
    if (argc == 1) {
        cerr << "Usage: ncc <file>" << endl;
        return 1;
    }

    lexer(argv[1]);

    return 0;
}

