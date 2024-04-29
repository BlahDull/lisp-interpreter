#include "../headers/EnvironmentContainer.hh"

// Method to search through the Environments to find the definition of something
Atom EnvironmentContainer::lookup(string name) {
    auto environment_copy = environments;
    while (!environment_copy.empty()) {
        Atom found_name = environment_copy.top().search(name);
        if (found_name.token_val == UNDEFINED) {
            environment_copy.pop();
        } else {
            return found_name;
        }
    }
    // If no definition is found, return an UNDEFINED Atom
    return Atom(UNDEFINED);
}

// Constructor
EnvironmentContainer::EnvironmentContainer() {

}

// Constructor to ensure that only one instance of the Environment Container class can be created
EnvironmentContainer* EnvironmentContainer::getInstance() {
    if (instance == nullptr) {
        instance = new EnvironmentContainer();
    }
    return instance;
}

// Method to add another environment to the environment container
void EnvironmentContainer::push_environment(Environment env) {
    environments.push(env);
}