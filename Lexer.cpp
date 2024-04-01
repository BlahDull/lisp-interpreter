#include "Lexer.hh"

TokenStream Lexer::tokenize_input(string input) {
        vector<Token> tokens;
        for (size_t i = 0; i < input.size(); i++) {
            if (input.at(i) == SPACE) continue;
            else if (input.at(i) == LPAREN) tokens.push_back(Token(LPAREN));
            else if (input.at(i) == RPAREN) tokens.push_back(Token(RPAREN));
            else if (input.at(i) == PLUS) tokens.push_back(Token(PLUS));
            else if (input.at(i) == MULTIPLY) tokens.push_back(Tokens(MULTIPLY));
            else if (input.at(i) == DIVIDE) tokens.push_back(Tokens(DIVIDE));
            else if (input.at(i) == MINUS) {
                if (input.at(i+1) == SPACE) tokens.push_back(Token(MINUS));
                else {
                    stringstream ss;
                    string num;
                    ss << "-";
                    i++;
                    while (isdigit(input.at(i))) {
                        ss << input.at(i);
                        i++;
                    }
                    i--;
                    ss >> num;
                    tokens.push_back(Token(num, LITERAL));
                }
            } else if (isdigit(input.at(i))){
                stringstream ss;
                string num;
                while (isdigit(input.at(i))) {
                    ss << input.at(i);
                    i++;
                }
                i--;
                ss >> num;
                tokens.push_back(Token(num, LITERAL));
            } else {
                stringstream ss;
                string symbol;
                while (input.at(i) != RPAREN && input.at(i) != ' ') {
                    ss << input.at(i);
                    i++;
                }
                i--;
                ss >> symbol;
                //if (in_keywords(symbol)) tokens.push_back(Token(symbol, KEYWORD));
                if (symbol == "T" || symbol == "F") tokens.push_back(Token(symbol, LITERAL));
                else tokens.push_back(Token(symbol, SYMBOL));
            }
        }
        return tokens;
}