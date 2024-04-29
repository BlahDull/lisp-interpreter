// Header file that contains the InputStream class prototype

#ifndef Lexer_H
#define Lexer_H
#include "libs.hh"
#include "InputStream.hh"

class Lexer {
public:
    InputStream tokenize_input(string x);
};

#endif