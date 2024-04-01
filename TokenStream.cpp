#include "TokenStream.hh"

TokenStream::TokenStream(vector<Token> input_tokens) {
    tokens = input_tokens;
}

Token TokenStream::eat(void) {
        Token token = *tokens.begin();
        if (!tokens.empty()) {
            tokens.erase(tokens.begin());
        }
        return token;
}

void TokenStream::print_tokens(void) {
    cout << "[ ";
    for (Token token : tokens) {
        if (token.is_token) cout << "'" << token.token_val << "' ";
        else cout << "'" << token.data_val << "' ";
    }
    cout << "]" << endl;
}

void TokenStream::push_front(void) {

}

void TokenStream::push_back(Token token) {
    tokens.push_back(token);
}