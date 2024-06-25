#!/bin/sh

g++ -Wall -Wextra main.cpp lexer.cpp -o main && \
    ./main source.ncc
