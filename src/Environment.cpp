#include "../headers/Environment.hh"

Atom Environment::search(string name) {
    auto it = symbol_table.find(name);
    if (it == symbol_table.end()) {
        return Atom(UNDEFINED);
    }
    return symbol_table.at(name);
}

void Environment::add_symbol(string name, Atom expression) {
    symbol_table.insert_or_assign(name, expression);
}