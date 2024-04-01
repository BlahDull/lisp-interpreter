#ifndef TokenStream_H
#define TokenStream_H
#include "libs.hh"
#include "Token.hh"

class TokenStream {
public:
    TokenStream(vector<Token> x);
    void push_front(void);
    Token eat(void);
    void clear(void);
    void print_tokens(void);
    void push_back(Token x);
private:
    vector<Token> tokens;
};

#endif