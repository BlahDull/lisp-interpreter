#include "../headers/Atom.hh"

Atom::Atom(unsigned char token_val) {
    this->token_val = token_val;
    this->is_token = true;
}

Atom::Atom(unsigned char type, string value) {
    this->value = value;
    switch (type) {
        case NUMBER:
            is_number = true;
            break;
        case SYMBOL:
            is_symbol = true;
            break;
        case LITERAL:
            is_literal = true;
            break;
    }
}

Atom::Atom(unsigned char type, vector<string> formal_parameters, string operation, string name) {
    is_function = true;
    this->formal_parameters = formal_parameters;
    this->operation = operation;
    this->value = name;
}