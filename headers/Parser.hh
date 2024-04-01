#ifndef Parser_H
#define Parser_H

#include "libs.hh"
#include "TokenStream.hh"
#include "Token.hh"

class Parser{
public:
    void parse(TokenStream x);
private:
    Token evaluate(TokenStream *x);
    Token eval_arithmetic(TokenStream *x, Token y);
    Token eval_keyword(TokenStream *x, Token y);
};

#endif