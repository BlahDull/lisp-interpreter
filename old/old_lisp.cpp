#include "libs.hh"

#define token_stream vector<Token>

class Symbol {
    public:
        string symbol_name = "";
        string expression = "";
        bool is_variable = false;
        bool is_func = false;
        Symbol(string name, string exp, unsigned char type) {
            expression = exp;
            if (isdigit(expression.at(0))) {
                is_variable = true;
            } else {
                is_func = true;
            }
        }
};

unordered_map<string, Symbol> symbol_table;
vector<string> keywords = {"set!", "define", "car", "cdr", "cons", "sqrt", "pow", "defun", "if"};

class Token {
    public:
        unsigned char token_val = EMPTY;
        string data_val = "";
        bool is_token = false;
        bool is_symbol = false;
        bool is_literal = false;
        bool is_keyword = false;

        Token(unsigned char token) {
            token_val = token;
            is_token = true;
        }

        Token(string val, unsigned char type) {
            switch(type) {
                case LITERAL:
                    data_val = val;
                    is_literal = true;
                    break;
                case SYMBOL:
                    data_val = val;
                    is_symbol = true;
                    break;
                case KEYWORD:
                    data_val = val;
                    is_keyword = true;
                    break;
            }
        }
};

class Lexer {
    public:
        token_stream tokenize_input(string input) {
            token_stream tokens;
            if (!check_parenthesis(input)) {
                cout << "ERROR: Invalid Parenthesis" << endl;
                return tokens;
            }
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
                    if (in_keywords(symbol)) tokens.push_back(Token(symbol, KEYWORD));
                    else if (symbol == "T" || symbol == "F") tokens.push_back(Token(symbol, LITERAL));
                    else tokens.push_back(Token(symbol, SYMBOL));
                }
            }
            return tokens;
        }
    private:
        bool check_parenthesis(string input) {
            stack<char> paren_stack;
            for (char c : input) {
                if (c == LPAREN) {
                    paren_stack.push(c);
                } else if (c == RPAREN) {
                    if (paren_stack.empty() || paren_stack.top() != LPAREN) return false;
                    paren_stack.pop();
                }
            }
            return paren_stack.empty();
        }

        bool in_keywords(string symbol) {
            for (string keyword : keywords) {
                if (keyword == symbol) return true;
            }
            return false;
        }

};

void print_tokens(vector<Token> *tokens) {
    cout << "[ ";
    for (Token token : *tokens) {
        if (token.is_token) cout << "'" << token.token_val << "' ";
        else cout << "'" << token.data_val << "' ";
    }
    cout << "]" << endl;
}

class Parser {
    public:
        void parse(token_stream tokens) {
            if (tokens.empty()) return;
            Token result = parse_expression(&tokens);
            cout << result.data_val << endl;
        }
    private:
        Token eat(token_stream *vec) {
            Token token = *vec->begin();
            if (!vec->empty()) {
                vec->erase(vec->begin());
            }
            //print_tokens(vec);
            return token;
        }

        void push(vector<Token> *vec, Token token) {
            vec->insert(vec->begin(), token);
        }

        Token define(token_stream *tokens) {
            Token token = eat(tokens);
            string name = token.data_val;
            string value = parse_expression(tokens).data_val;
            Symbol symbol = Symbol(name, value, VARIABLE);
            symbol_table.insert_or_assign(name, symbol);
            return Token(name, LITERAL);
        }

        Token defun(token_stream *tokens) {

        }


        Token parse_expression(token_stream *tokens) {
            Token token = eat(tokens);
            if (token.is_literal) return token;
            if (token.is_symbol) return Token(symbol_table.at(token.data_val).expression, LITERAL);
            if (token.token_val == LPAREN) {
                while (token.token_val != RPAREN) {
                    token = eat(tokens);
                    unsigned char token_val = token.token_val;
                    switch (token_val) {
                        case PLUS: {
                            int operand1 = stoi(parse_expression(tokens).data_val);
                            int operand2 = stoi(parse_expression(tokens).data_val);
                            token = eat(tokens);
                            if (token.token_val == RPAREN) {
                                return Token(to_string(operand1 + operand2), LITERAL);
                            } else {
                                push(tokens, token);
                                push(tokens, Token(to_string(operand1 + operand2), LITERAL));
                                push(tokens, Token(PLUS));
                            }
                            break;
                        }
                        case MINUS: {
                            int operand1 = stoi(parse_expression(tokens).data_val);
                            int operand2 = stoi(parse_expression(tokens).data_val);
                            token = eat(tokens);
                            if (token.token_val == RPAREN) {
                                return Token(to_string(operand1 - operand2), LITERAL);
                            } else {
                                push(tokens, token);
                                push(tokens, Token(to_string(operand1 - operand2), LITERAL));
                                push(tokens, Token(MINUS));
                            }
                            break;
                        }
                        case MULTIPLY: {
                            int operand1 = stoi(parse_expression(tokens).data_val);
                            int operand2 = stoi(parse_expression(tokens).data_val);
                            token = eat(tokens);
                            if (token.token_val == RPAREN) {
                                return Token(to_string(operand1 * operand2), LITERAL);
                            } else {
                                push(tokens, token);
                                push(tokens, Token(to_string(operand1 * operand2), LITERAL));
                                push(tokens, Token(MULTIPLY));
                            }
                            break;
                        }
                        case DIVIDE: {
                            int operand1 = stoi(parse_expression(tokens).data_val);
                            int operand2 = stoi(parse_expression(tokens).data_val);
                            token = eat(tokens);
                            if (operand2 == 0) {
                                cout << "ERROR: Division by 0" << endl;
                                return Token(EMPTY);
                            }
                            if (token.token_val == RPAREN) {
                                return Token(to_string(operand1 / operand2), LITERAL);
                            } else {
                                push(tokens, token);
                                push(tokens, Token(to_string(operand1 / operand2), LITERAL));
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
                            if (token.is_literal) return token;
                            else if (token.is_keyword) {
                                if (token.data_val == "define") return token = define(tokens);
                                if (token.data_val == "defun") return token = defun(tokens);
                            } else if (token.is_symbol) return Token(symbol_table.at(token.data_val).expression, LITERAL) ;
                        }
                    }
                }
            }
            cout << "ERROR: Unknown" << endl;
            return Token(EMPTY);
        }
};

int main() {
    string input;
    cout << "Welcome to the Lisp Interpreter. Type in Lisp Commands!" << endl;
    while (1) {
        cout << ">";
        getline(cin, input);
        if (input == "bye") break;
        Lexer lexer = Lexer();
        token_stream tokens = lexer.tokenize_input(input);
        print_tokens(&tokens);
        Parser parser = Parser();
        parser.parse(tokens);
    }
    return 0;
}