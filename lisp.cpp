#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
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
    TRUE = 'T',
    FALSE = 'F',
    NOP = '_'
};

unordered_map<string, float> symbol_table;
vector<string> keywords = {"set!", "define", "car", "cdr", "cons", "sqrt", "pow", "defun", "if"};

class Token {
    public:
        unsigned char token_val = NOP;
        string number_val = "";
        string symbol = "";
        bool is_number = false;
        bool is_symbol = false;
        bool is_operator = false;
        bool is_boolean = false;

        Token(unsigned char input) {
            token_val = input;
            if (input == TRUE || input == FALSE) {is_boolean = true;} else {is_operator = true;}
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
                if (!isdigit(c) && c != '.' && c != '-') {
                    return false;
                }
            }
            return true;
        }
};
// Decimals are incorrectly split into two tokens, for example 2.1 gets turned into '2' and '.1'
class Lexer {
    public:
        vector<Token> tokens;
        void tokenize(string input_str) {
            if (!check_parenthesis(input_str)) {
                cout << "Error: Invalid Parenthesis." << endl;
                return;
            }
            for (size_t i = 0; i < input_str.length(); i++) {
                if (input_str.at(i) == ' ') continue;
                else if (input_str.at(i) == '+') {
                    tokens.push_back(Token(PLUS));
                }
                else if (input_str.at(i) == '-') {
                    if (isdigit(input_str.at(i+1))) {
                        stringstream ss;
                        string num;
                        ss << "-";
                        i++;
                        while (isdigit(input_str.at(i))) {
                            ss << input_str.at(i);
                            i++;
                        }
                        i--;
                        ss >> num;
                        tokens.push_back(Token(num));
                    } else {
                        tokens.push_back(Token(MINUS));
                    }
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
                else if (input_str.at(i) == 'T' || input_str.at(i) == 'F') {
                    tokens.push_back(Token(input_str.at(i)));
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

        bool check_parenthesis(string input) {
            stringstream ss;
            string parens;
            for (char c : input) {
                if (c == LPAREN || c == RPAREN) ss << c;
            }
            ss >> parens;
            if (parens.length() % 2 != 0) return false;
            stack<char> paren_stack;
            for (char c : parens) {
                if (c == LPAREN) {
                    paren_stack.push(c);
                } else {
                    if (paren_stack.empty() || paren_stack.top() != LPAREN) return false;
                    paren_stack.pop();
                }
            }
            return paren_stack.empty();
        }
};

void print_tokens(vector<Token> *tokens) {
    cout << "[ ";
    for (Token token : *tokens) {
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

class Parser {
    public:
        void parse(vector<Token> tokens) {
            while(!tokens.empty()) {
                // string result = parse_expression(&tokens).number_val;
                // if (result.size() == 0) return;
                // cout << truncate_zeros(result) << endl;
                Token result = parse_expression(&tokens);
                if (result.is_number) {
                    cout << truncate_zeros(result.number_val) << endl;
                } else if (result.is_boolean) {
                    cout << result.token_val << endl;
                } else if (result.is_symbol) {
                    cout << result.symbol << endl;
                }
            }
        }

    private:

        Token eat(vector<Token> *vec) {
            Token token = *vec->begin();
            if (!vec->empty()) {
                vec->erase(vec->begin());
            }
            //print_tokens(vec);
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
            } else if (!is_keyword(token.symbol) && token.is_symbol) {
                //cout << token.symbol << " is not a keyword\n"; 
                string variable_name = token.symbol;
                //cout << to_string(symbol_table.at(variable_name)) << endl;
                return Token(to_string(symbol_table.at(variable_name)));
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
                            if (token.token_val == ')') {
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
                            if (token.token_val == ')') {
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
                            if (token.token_val == ')') {
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
                                cout << "Attempted division by 0. Aborting..." << endl;
                                tokens->clear();
                                return Token(NOP);
                            }
                            token = eat(tokens);
                            if (token.token_val == ')') {
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

                        case RPAREN: {
                            break;
                        }

                        default: {
                            if (is_keyword(token.symbol)) {
                                if (token.symbol == "define") {
                                    token = eat(tokens);
                                    string variable_name = token.symbol;
                                    float variable_value = stof(parse_expression(tokens).number_val);
                                    //cout << variable_name << ":= " << variable_value << endl;
                                    symbol_table.insert_or_assign(variable_name, variable_value);
                                    return Token(variable_name);
                                }

                                if (token.symbol == "defun") {
                                    
                                }
                            } else if (token.is_number) {
                                return token;
                            } else if (token.is_boolean) {
                                return token;
                            }
                        }
                    }
                }
            }
            return Token(NOP);
        }

        bool is_keyword(string word) {
            for (string keyword : keywords) {
                if (word == keyword) return true;
            }
            return false;
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
        cout << ">";
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
