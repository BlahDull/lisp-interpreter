#include "libs.hh"
#include "InputStream.hh"
#include "Lexer.hh"
#include "Parser.hh"
#include "EnvironmentContainer.hh"

// Initialzing the Environment Container
EnvironmentContainer* EnvironmentContainer::instance = nullptr;

// Main loop which will retrieve user input until they enter (quit)
int main() {
    string input;
    EnvironmentContainer* container = EnvironmentContainer::getInstance();
    Lexer lexer;
    Parser parser;
    puts("Welcome to the Lisp Interpreter! Type in Lisp Commands. Type (quit) to exit.");
    while (1) {
        cout << ">";
        getline(cin, input);
        if (input == "(quit)") break;
        InputStream stream = lexer.tokenize_input(input);
        //stream.print_tokens();
        parser.parse_tokens(stream);
    }
}