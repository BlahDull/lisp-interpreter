#include "../headers/Environment.hh"

// Method to search the environment for a symbol, if none is found, return UNDEFINED Atom
Atom Environment::search(string name) {
    auto it = symbol_table.find(name);
    if (it == symbol_table.end()) {
        return Atom(UNDEFINED);
    }
    return symbol_table.at(name);
}

// Method to insert a new symbol into the environment
void Environment::add_symbol(string name, Atom expression) {
    symbol_table.insert_or_assign(name, expression);
}