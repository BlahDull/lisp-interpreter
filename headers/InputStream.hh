#ifndef InputStream_H
#define InputStream_H
#include "libs.hh"
#include "Atom.hh"

class InputStream {
public:
    Atom eat();
    Atom peek();
    void push_front(Atom x);
    void push_back(Atom x);
    void print_tokens();
    bool is_empty();
private:
    vector<Atom> stream;
};

#endif