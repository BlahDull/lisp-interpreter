#ifndef EnvironmentContainer_H
#define EnvironmentContainer_H
#include "libs.hh"
#include "Environment.hh"
#include "Atom.hh"

class EnvironmentContainer {
public:
    static EnvironmentContainer* instance;

    Atom lookup(string x);
    static EnvironmentContainer* getInstance();
    void push_environment(Environment x);
private:
    EnvironmentContainer();
    stack<Environment> environments;
};

#endif