#include "Token.hh"
#include "TokenStream.hh"
#include "Lexer.hh"
#include "Parser.hh"
#include "libs.hh"

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
    }
}