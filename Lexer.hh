#ifndef Lexer_H
#define Lexer_H
#include "libs.hh"
#include "TokenStream.hh"
#include "Token.hh"

class Lexer {
public:
    TokenStream tokenize_input(string x);
};

#endif