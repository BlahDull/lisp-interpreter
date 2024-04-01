#include "../headers/Token.hh"
#include "../headers/TokenStream.hh"
#include "../headers/Lexer.hh"
#include "../headers/Parser.hh"
#include "../headers/libs.hh"

int main() {
    string input;
    puts("Welcome to the Lisp Interpreter. Type in Lisp Commands!");
    while (1) {
        cout << ">";
        getline(cin, input);
        if (input == "bye") break;
        Lexer lexer;
        TokenStream tokens = TokenStream(lexer.tokenize_input(input));
        tokens.print_tokens();
        Parser parser;
        parser.parse(tokens);
    }
}