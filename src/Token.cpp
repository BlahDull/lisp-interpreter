#include "../headers/Token.hh"

Token::Token(unsigned char type) {
    this->is_token = true;
    this->token_val = type;
}

Token::Token(string data, unsigned char type) {
    this->data_val = data;
    this->token_val = EMPTY;
    switch (type) {
        case LITERAL:
            this->is_literal = true;
            break;
        case SYMBOL:
            this->is_symbol = true;
            break;
        case KEYWORD:
            this->is_keyword = true;
            break;
    }
}  