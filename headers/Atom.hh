#ifndef Atom_H
#define Atom_H
#include "libs.hh"

class Atom {
public:
    unsigned char token_val = EMPTY;
    string value = "";
    vector<string> formal_parameters;
    string operation = "";
    bool is_token = false;
    bool is_number = false;
    bool is_symbol = false;
    bool is_literal = false;
    bool is_function = false;
    Atom(unsigned char x);
    Atom(unsigned char x, string y);
    Atom(unsigned char x, vector<string> y, string z, string w);
};

#endif