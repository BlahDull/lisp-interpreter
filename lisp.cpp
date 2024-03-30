#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>
#include <unordered_map>

using namespace std;

// (+ (+ 3 4) 5)

enum Tokens {
    PLUS = '+',
    MINUS = '-',
    MULTIPLY = '*',
    DIVIDE = '/',
    LPAREN = '(',
    RPAREN = ')',
    NOP = '_'
};

class Token {
    public:
        unsigned char token_val = NOP;
        string number_val = "";
        string symbol = "";
        bool is_number = false;
        bool is_symbol = false;

        Token(unsigned char input) {
            token_val = input;
        }

        Token(string input) {
            if (contains_number(input)) {
                number_val = input;
                is_number = true;
            } else {
                symbol = input;
                is_symbol = true;
            }
        }
    private:
        bool contains_number(string input) {
            for (char c : input) {
                if (!isdigit(c) && c != '.') {
                    return false;
                }
            }
            return true;
        }
};

class Lexer {
    public:
        vector<Token> tokens;
        void tokenize(string input_str) {
            for (size_t i = 0; i < input_str.length(); i++) {
                if (input_str.at(i) == ' ') continue;
                else if (input_str.at(i) == '+') {
                    tokens.push_back(Token(PLUS));
                }
                else if (input_str.at(i) == '-') {
                    tokens.push_back(Token(MINUS));
                }
                else if (input_str.at(i) == '*') {
                    tokens.push_back(Token(MULTIPLY));
                }
                else if (input_str.at(i) == '/') {
                    tokens.push_back(Token(DIVIDE));
                }
                else if (input_str.at(i) == '(') {
                    tokens.push_back(Token(LPAREN));
                }
                else if (input_str.at(i) == ')') {
                    tokens.push_back(Token(RPAREN));
                }
                else if (isdigit(input_str.at(i))) {
                    stringstream ss;
                    string num;
                    while (isdigit(input_str.at(i))) {
                        ss << input_str.at(i);
                        i++;
                    }
                    i--;
                    ss >> num;
                    tokens.push_back(Token(num));
                } else {
                    stringstream ss;
                    string term;
                    while (input_str.at(i) != RPAREN && input_str.at(i) != ' ') {
                        ss << input_str.at(i);
                        i++;
                    }
                    i--;
                    ss >> term;
                    tokens.push_back(Token(term));
                }
            }
        }
};

void print_tokens(vector<Token> *tokens) {
    cout << "[ ";
    for (Token token : *tokens) {        vector<string> keywords = {"set!", "define", "car", "cdr", "cons", "sqrt", "pow", "defun", "if"};
        if (!token.is_number && !token.is_symbol) {
            cout << "'" << token.token_val << "' ";
        } else  if (token.is_number) {
            cout << "'" << token.number_val << "' ";
        } else if (token.is_symbol) {
            cout << "'" << token.symbol << "' ";
        }
    }
    cout << "]" << endl;
}

void print_map(unordered_map<string, float> map) {
    for (auto entry : map) {
        cout << entry.first << ": " << entry.second << endl;
    }
}

unordered_map<string, float> symbol_table;
vector<string> keywords = {"set!", "define", "car", "cdr", "cons", "sqrt", "pow", "defun", "if"};

class Parser {
    public:
        void parse(vector<Token> tokens) {
            while(!tokens.empty()) {
                string result = parse_expression(&tokens).number_val;
                if (result.size() == 0) return;
                cout << truncate_zeros(result) << endl;
            }
        }

    private:

        Token eat(vector<Token> *vec) {
            Token token = *vec->begin();
            if (!vec->empty()) {
                vec->erase(vec->begin());
            }
            return token;
        }

        Token look_ahead(vector<Token> *vec) {
            if (vec->size() > 1) {
                Token token = vec->at(1);
                return token;
            } else {
                return vec->at(0);
            }
        }

        void push(vector<Token> *vec, Token token) {
            vec->insert(vec->begin(), token);
        }

        Token parse_expression(vector<Token> *tokens) {
            Token token = eat(tokens);
            if (token.is_number) {
                return token;
            }
            if (token.token_val == LPAREN) {
                while (token.token_val != RPAREN) {
                    token = eat(tokens);
                    unsigned char val = token.token_val;
                    switch (val) {
                        case PLUS: {
                            float operand1 = stof(parse_expression(tokens).number_val);
                            float operand2 = stof(parse_expression(tokens).number_val);
                            token = eat(tokens);
                            if (!token.is_number) {
                                return Token(to_string(operand1 + operand2));
                            } else {
                                push(tokens, token);
                                push(tokens, Token(to_string(operand1 + operand2)));
                                push(tokens, Token(PLUS));
                            }
                            break;
                        }
                        case MINUS: {
                            float operand1 = stof(parse_expression(tokens).number_val);
                            float operand2 = stof(parse_expression(tokens).number_val);
                            token = eat(tokens);
                            if (!token.is_number) {
                                return Token(to_string(operand1 - operand2));
                            } else {
                                push(tokens, token);
                                push(tokens, Token(to_string(operand1 - operand2)));
                                push(tokens, Token(MINUS));
                            }
                            break;
                        }
                        case MULTIPLY: {
                            float operand1 = stof(parse_expression(tokens).number_val);
                            float operand2 = stof(parse_expression(tokens).number_val);
                            token = eat(tokens);
                            if (!token.is_number) {
                                return Token(to_string(operand1 * operand2));
                            } else {
                                push(tokens, token);
                                push(tokens, Token(to_string(operand1 * operand2)));
                                push(tokens, Token(MULTIPLY));
                            }
                            break;
                        }
                        case DIVIDE: {
                            float operand1 = stof(parse_expression(tokens).number_val);
                            float operand2 = stof(parse_expression(tokens).number_val);
                            if (operand2 == 0) {
                                cout << "Attempted division by 0. Aborting...";
                                tokens->clear();
                                return Token(NOP);
                            }
                            token = eat(tokens);
                            if (!token.is_number) {
                                return Token(to_string(operand1 / operand2));
                            } else {
                                push(tokens, token);
                                push(tokens, Token(to_string(operand1 / operand2)));
                                push(tokens, Token(DIVIDE));
                            }
                            break;
                        }

                        case LPAREN: {
                            push(tokens, parse_expression(tokens));
                            break;
                        }
                        default: {
                            if (token.symbol == "define") {
                                token = eat(tokens);
                                string variable_name = token.symbol;
                                float variable_value = stof(parse_expression(tokens).number_val);
                                symbol_table.insert(make_pair(variable_name, variable_value));
                            }
                        }
                    }
                }
            }
            return Token(NOP);
        }

        string truncate_zeros(string str) {
            int index = str.find(".");
            for (size_t i = index + 1; i < str.size(); i++) {
                if (str.at(i) != '0') {
                    return str;
                }
            }
            return str.substr(0, index);
        }
};

int main()
{
    string input;
    cout << "Welcome to the Lisp Interpreter. Type in Lisp Commands!" << endl;
    while (1) {
        getline(cin, input);
        //input = "(+ (+ (+ 5 3) 2) (- 4 3))";
        //input = "(/ 20 6 2)";
        if (input == "bye") break;
        Lexer lexer = Lexer();
        lexer.tokenize(input);
        print_tokens(&lexer.tokens);
        Parser parser = Parser();
        parser.parse(lexer.tokens);
    }
    return 0;
}
