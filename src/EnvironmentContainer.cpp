#include "../headers/EnvironmentContainer.hh"

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
    return Atom(UNDEFINED);
}

EnvironmentContainer::EnvironmentContainer() {

}

EnvironmentContainer* EnvironmentContainer::getInstance() {
    if (instance == nullptr) {
        instance = new EnvironmentContainer();
    }
    return instance;
}

void EnvironmentContainer::push_environment(Environment env) {
    environments.push(env);
}