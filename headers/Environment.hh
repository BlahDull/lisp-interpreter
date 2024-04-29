// Header file that contains the Environment class prototype

#ifndef Environment_H
#define Environment_H

#include "libs.hh"
#include "Atom.hh"

class Environment{
public:
    Atom search(string x);
    void add_symbol(string x, Atom y);
    void set_symbol(string x, Atom y);
private:
    unordered_map<string, Atom> symbol_table;
};

#endif