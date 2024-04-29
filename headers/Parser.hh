// Header file that contains the Parser class prototype

#ifndef Parser_H
#define Parser_H
#include "libs.hh"
#include "InputStream.hh"

class Parser {
public:
    void parse_tokens(InputStream stream);
private:
    Atom evaluate(InputStream *stream);
    Atom eval_arithmetic(Atom atom, InputStream *stream);
    Atom my_sqrt(InputStream *stream);
    Atom my_pow(InputStream *stream);
    Atom define(InputStream *stream);
    Atom set(InputStream *stream);
    Atom search_for_symbol(string symbol_name);
    Atom car(InputStream *stream);
    Atom cdr(InputStream *stream);
    Atom cons(InputStream *stream);
    Atom eval_boolean(Atom atom, InputStream *stream);
    Atom defun(InputStream *stream);
    Atom eval_function(Atom function, InputStream *stream);
    bool check_if_boolean(Atom atom);
    bool check_parenthesis(InputStream stream);
};

#endif