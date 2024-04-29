#include "../headers/Lexer.hh"

InputStream Lexer::tokenize_input(string input) {
    InputStream stream;
    for (size_t i = 0; i < input.size(); i++) {
        unsigned char c = input.at(i);
        if (c == SPACE) continue;
        else if (c == LPAREN) stream.push_back(Atom(LPAREN));
        else if (c == RPAREN) stream.push_back(Atom(RPAREN));
        else if (c == PLUS) stream.push_back(Atom(PLUS));
        else if (c == MULTIPLY) stream.push_back(Atom(MULTIPLY));
        else if (c == DIVIDE) stream.push_back(Atom(DIVIDE));
        else if (c == LESS_THAN) {
            if (input.at(i+1) == EQUAL) {
                stream.push_back(Atom(LESS_THAN_EQUAL));
                i++;
            } else {
                stream.push_back(Atom(LESS_THAN));
            }
        }
        else if (c == GREATER_THAN) {
            if (input.at(i+1) == EQUAL) {
                stream.push_back(Atom(GREATER_THAN_EQUAL));
                i++;
            } else {
                stream.push_back(Atom(GREATER_THAN));
            }
        }
        else if (c == EQUAL) {
            stream.push_back(Atom(EQUAL));
            if (input.at(i+1) == EQUAL) i++;
        }
        else if (c == TRUE && (input.at(i+1) == RPAREN || input.at(i+1) == SPACE)) stream.push_back(Atom(TRUE));
        else if (c == NOT) {
            if (input.at(i+1) == EQUAL) {
                i++;
                stream.push_back(Atom(NOT_EQUAL));
            } else {
                stream.push_back(Atom(NOT));
            }
        }
        else if (c == MINUS) {
            if (input.at(i+1) == SPACE) {
                stream.push_back(Atom(MINUS));
            } else {
                stringstream ss;
                string number;
                ss << "-";
                i++;
                while (isdigit(input.at(i))) {
                    ss << input.at(i);
                    i++;
                }
                i--;
                ss >> number;
                stream.push_back(Atom(NUMBER, number));
            }
        } else if (isdigit(c)) {
                stringstream ss;
                string number;
                while (isdigit(input.at(i))) {
                    ss << input.at(i);
                    i++;
                }
                i--;
                ss >> number;
                if (stoll(number) > INT_MAX || stoll(number) < INT_MIN) {
                    cout << "INTEGER OVERFLOW ERROR" << endl;
                    InputStream blank;
                    return blank;
                }
                stream.push_back(Atom(NUMBER, number)); 
        } else if (c == QUOTE) {
            int open_paren = 0, close_paren = 0;
            stringstream ss;
            string expression = "";
            i++;
            if (input.at(i) == LPAREN) {
                do
                {
                    if (input.at(i) == LPAREN) open_paren++;
                    else if (input.at(i) == RPAREN) close_paren++;
                    expression = expression + input.at(i);
                    i++;
                } while (open_paren != close_paren);
            } else {
                while (input.at(i) != SPACE && input.at(i) != RPAREN) {
                    expression = expression + input.at(i);
                    i++;
                }
            }
            stream.push_back(Atom(LITERAL, expression));
        } else {
            stringstream ss;
            string symbol;
            while(input.at(i) != SPACE && input.at(i) != RPAREN) {
                ss << input.at(i);
                i++;
            }
            i--;
            ss >> symbol;
            if (symbol == "and") {
                stream.push_back(Atom(AND));
            } else if (symbol == "or") {
                stream.push_back(Atom(OR));
            } else if (symbol == "NIL" || symbol == "nil") {
                stream.push_back(Atom(NIL));
            } else if (symbol == "not") {
                stream.push_back(Atom(NOT));
            } else if (symbol == "if") {
                stream.push_back(Atom(IF));
            } else {
                stream.push_back(Atom(SYMBOL, symbol));
            }
        }
    }
    return stream;
}