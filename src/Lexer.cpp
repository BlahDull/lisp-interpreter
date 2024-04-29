#include "../headers/Lexer.hh"

/**
 * This class is responsible for taking in the Lisp command input string and converting it into a stream of tokens.
 * It will go through the string and check each character to make sure that the token is created properly, thne it will add it to the InputStream.
 * It will then return the InputStream once it has reached the end of the string.
*/
InputStream Lexer::tokenize_input(string input) {
    // The stream that will be returned
    InputStream stream;
    // For loop that will go through the string and create tokens based on the input
    for (size_t i = 0; i < input.size(); i++) {
        unsigned char c = input.at(i);
        // This else if chain will create different tokens depending on the character that it is currently at
        if (c == SPACE) continue;
        else if (c == LPAREN) stream.push_back(Atom(LPAREN));
        else if (c == RPAREN) stream.push_back(Atom(RPAREN));
        else if (c == PLUS) stream.push_back(Atom(PLUS));
        else if (c == MULTIPLY) stream.push_back(Atom(MULTIPLY));
        else if (c == DIVIDE) stream.push_back(Atom(DIVIDE));
        // Code block to check if the token should be < or <=
        else if (c == LESS_THAN) {
            if (input.at(i+1) == EQUAL) {
                stream.push_back(Atom(LESS_THAN_EQUAL));
                i++;
            } else {
                stream.push_back(Atom(LESS_THAN));
            }
        }
        // Code block to check if the token should be > or >=
        else if (c == GREATER_THAN) {
            if (input.at(i+1) == EQUAL) {
                stream.push_back(Atom(GREATER_THAN_EQUAL));
                i++;
            } else {
                stream.push_back(Atom(GREATER_THAN));
            }
        }
        // Code block to make sure an equal sign has another equal sign following it, representing equality operator ==
        // If not, the equal sign will be treated as a symbol
        else if (c == EQUAL) {
            stream.push_back(Atom(EQUAL));
            if (input.at(i+1) == EQUAL) i++;
        }
        // Code block to make sure that T represents the boolean operator, not part of a larger word
        else if (c == TRUE && (input.at(i+1) == RPAREN || input.at(i+1) == SPACE)) stream.push_back(Atom(TRUE));
        // Code block to check if the not is to negate a boolean expression, or as a part of !=
        else if (c == NOT) {
            if (input.at(i+1) == EQUAL) {
                i++;
                stream.push_back(Atom(NOT_EQUAL));
            } else {
                stream.push_back(Atom(NOT));
            }
        }
        // Code block to check if a minus sign is for subtraction or to signify a negative integer
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
        // Code block to create tokens that represent digits
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
        // Code block to create tokens that represent quote literals
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
        // Code block that will create tokens that didn't match any other token, ie. variable names or boolean operators.
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
    // Returning the InputStream which contains the tokens
    return stream;
}