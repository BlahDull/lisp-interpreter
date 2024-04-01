#ifndef Token_H
#define Token_H
#include "libs.hh"

using namespace std;

class Token {
public:
    unsigned char token_val = EMPTY;
    string data_val = "";
    bool is_token = false;
    bool is_symbol = false;
    bool is_literal = false;
    bool is_keyword = false;
    Token(unsigned char x);
    Token(string x, unsigned char y);
};

#endif