#include "Parser.hh"
#include "Lexer.hh"
#include "EnvironmentContainer.hh"

void Parser::parse_tokens(InputStream stream) {
    if (stream.is_empty()) return;
    Atom result = evaluate(&stream);
    ofstream file("results.txt", ios::app);
    if (result.is_token) {
        if (result.token_val == NIL) {
            file << "NIL\n";
            cout << "NIL" << endl;
        } else if (result.token_val == UNDEFINED) {
            file << "UNDEFINED VALUE\n";
            cout << "UNDEFINED VALUE" << endl;
        } else {
            file << result.token_val << "\n";
            cout << result.token_val << endl;
        }
    } else {
        if (result.is_number) {
            if (stol(result.value) > INT_MAX || stol(result.value) < INT_MIN) {
                cout << "INTEGER OVERFLOW ERROR" << endl;
                return;
            }
        }
        file << result.value << "\n";
        cout << result.value << endl;
    }
}

bool Parser::check_parenthesis(InputStream stream) {
    stack<unsigned char> parenthesis;
    while (!stream.is_empty()) {
        Atom top = stream.eat();
        if (top.token_val == LPAREN) {
            parenthesis.push(top.token_val);
        } else if (top.token_val == RPAREN) {
            if (parenthesis.empty()) {
                return false;
            } else {
                parenthesis.pop();
            }
        }
    }
    return parenthesis.empty();
}

Atom Parser::eval_arithmetic(Atom atom, InputStream *stream) {
    switch(atom.token_val) {
        case PLUS: {
            int operand1 = stoi(evaluate(stream).value);
            int operand2 = stoi(evaluate(stream).value);
            atom = stream->eat();
            if (atom.token_val == RPAREN) {
                return Atom(NUMBER, to_string(operand1 + operand2));
            }
            break;
        }
        case MINUS: {
            int operand1 = stoi(evaluate(stream).value);
            int operand2 = stoi(evaluate(stream).value);
            atom = stream->eat();
            if (atom.token_val == RPAREN) {
                return Atom(NUMBER, to_string(operand1 - operand2));
            }
            break;
        }
        case MULTIPLY: {
            int operand1 = stoi(evaluate(stream).value);
            int operand2 = stoi(evaluate(stream).value);
            atom = stream->eat();
            if (atom.token_val == RPAREN) {
                return Atom(NUMBER, to_string(operand1 * operand2));
            }
            break;
        }
        case DIVIDE: {
            int operand1 = stoi(evaluate(stream).value);
            int operand2 = stoi(evaluate(stream).value);
            atom = stream->eat();
            if (operand2 == 0) {
                puts("Error! Attempted division by 0");
                return Atom(ERROR, "ERR");
            }
            if (atom.token_val == RPAREN) {
                return Atom(NUMBER, to_string(operand1 / operand2));
            }
            break;
        }
    }
}

Atom Parser::define(InputStream *stream) {
    string variable_name = stream->eat().value;
    Atom evaluation = evaluate(stream);
    Environment env;
    env.add_symbol(variable_name, evaluation);
    EnvironmentContainer* container = EnvironmentContainer::getInstance();
    container->push_environment(env);
    return Atom(LITERAL, variable_name);
}

Atom Parser::search_for_symbol(string symbol_name) {
    EnvironmentContainer* container = EnvironmentContainer::getInstance();
    Atom result = container->lookup(symbol_name);
    return container->lookup(symbol_name);
}

Atom Parser::car(InputStream *stream) {
    int open_paren = 0, close_paren = 0, count = 0;
    Atom atom = evaluate(stream);
    string expression = atom.value;
    expression = expression.substr(1, expression.size() - 2);
    string first_element = "";
    do
    {
        first_element = first_element + expression.at(count);
        if (expression.at(count) == LPAREN) open_paren++;
        else if (expression.at(count) == RPAREN) close_paren++;
        count++;
    } while (open_paren != close_paren);
    return Atom(LITERAL, first_element);
}

Atom Parser::cdr(InputStream *stream) {
    int open_paren = 0, close_paren = 0, count = 0;
    Atom atom = evaluate(stream);
    string expression = atom.value;
    expression = expression.substr(1, expression.size() - 2);
    string remainder = "";
    do
    {
        if (expression.at(count) == LPAREN) open_paren++;
        else if (expression.at(count) == RPAREN) close_paren++;
        count++;
    } while (open_paren != close_paren);
    remainder = "(" + expression.substr(count + 1, expression.size() - 1) + ")";
    return Atom(LITERAL, remainder);
}

Atom Parser::eval_boolean(Atom atom, InputStream *stream) {
    switch (atom.token_val) {
        case LESS_THAN: {
            int operand1 = stoi(evaluate(stream).value);
            int operand2 = stoi(evaluate(stream).value);
            bool result = (operand1 < operand2);
            if (result == true) {
                return Atom(TRUE);
            } else {
                return Atom(NIL);
            }
            break;
        }
        case LESS_THAN_EQUAL: {
            int operand1 = stoi(evaluate(stream).value);
            int operand2 = stoi(evaluate(stream).value);
            bool result = (operand1 <= operand2);
            if (result == true) {
                return Atom(TRUE);
            } else {
                return Atom(NIL);
            }
            break;
        }
        case GREATER_THAN: {
            int operand1 = stoi(evaluate(stream).value);
            int operand2 = stoi(evaluate(stream).value);
            bool result = (operand1 > operand2);
            if (result == true) {
                return Atom(TRUE);
            } else {
                return Atom(NIL);
            }
            break;
        }
        case GREATER_THAN_EQUAL: {
            int operand1 = stoi(evaluate(stream).value);
            int operand2 = stoi(evaluate(stream).value);
            bool result = (operand1 >= operand2);
            if (result == true) {
                return Atom(TRUE);
            } else {
                return Atom(NIL);
            }
            break;
        }
        case EQUAL: {
            int operand1 = stoi(evaluate(stream).value);
            int operand2 = stoi(evaluate(stream).value);
            bool result = (operand1 == operand2);
            if (result == true) {
                return Atom(TRUE);
            } else {
                return Atom(NIL);
            }
            break;
        }
        case NOT_EQUAL: {
            int operand1 = stoi(evaluate(stream).value);
            int operand2 = stoi(evaluate(stream).value);
            bool result = (operand1 != operand2);
            if (result == true) {
                return Atom(TRUE);
            } else {
                return Atom(NIL);
            }
            break;
        }
        case AND: {
            Atom operand1 = evaluate(stream);
            // Eat the ')' from the last evaluation
            if (stream->peek().token_val == RPAREN) {
                atom = stream->eat();
            }
            Atom operand2 = evaluate(stream);
            if (operand1.token_val == TRUE && operand2.token_val == TRUE) {
                return Atom(TRUE);
            }
            return Atom(NIL);
            break;
        }
        case OR: {
            Atom operand1 = evaluate(stream);
            // Eat the ')' from the last evaluation
            if (stream->peek().token_val == RPAREN) {
                atom = stream->eat();
            }
            Atom operand2 = evaluate(stream);
            if (operand1.token_val == TRUE || operand2.token_val == TRUE) {
                return Atom(TRUE);
            }
            return Atom(NIL);
            break;
        }
        case NOT: {
            Atom operand = evaluate(stream);
            if (operand.token_val == TRUE) {
                return Atom(NIL);
            } else {
                return Atom(TRUE);
            }
            break;
        }
        case IF: {
            Atom evaluation = evaluate(stream);
            if (stream->peek().token_val == RPAREN) {
                atom = stream->eat();
            }
            if (evaluation.token_val == TRUE) {
                return evaluate(stream);
            } else {
                stack<char> parenthesis;
                atom = stream->eat();
                parenthesis.push(atom.token_val);
                while (!parenthesis.empty()) {
                    atom = stream->eat();
                    if (atom.token_val == LPAREN) {
                        parenthesis.push(atom.token_val);
                    } else if (atom.token_val == RPAREN){
                        parenthesis.pop();
                    }
                }
                return evaluate(stream);
            }
            break;
        }
        case TRUE: {
            return Atom(TRUE);
            break;
        }
        case NIL: {
            return Atom(NIL);
            break;
        }
    }
}

bool Parser::check_if_boolean(Atom atom) {
    if (atom.token_val == EQUAL || atom.token_val == NOT || atom.token_val == GREATER_THAN 
    || atom.token_val == LESS_THAN || atom.token_val == TRUE || atom.token_val == NOT_EQUAL
    || atom.token_val == AND || atom.token_val == OR || atom.token_val == IF || atom.token_val == NIL
    || atom.token_val == LESS_THAN_EQUAL || atom.token_val == GREATER_THAN_EQUAL) {
        return true;
    }
    return false;
}

Atom Parser::my_sqrt(InputStream *stream) {
    int operand = stoi(evaluate(stream).value);
    return Atom(NUMBER, to_string(sqrt(operand)));
}

Atom Parser::my_pow(InputStream *stream) {
    int base = stoi(evaluate(stream).value);
    int power = stoi(evaluate(stream).value);
    return Atom(NUMBER, to_string(pow(base, power)));
}

Atom Parser::defun(InputStream *stream) {
    string function_name = stream->eat().value;
    vector<string> formal_parameters;
    string operation = "";
    Atom atom = stream->eat();
    while (atom.token_val != RPAREN) {
        if (!atom.is_token) formal_parameters.push_back(atom.value);
        atom = stream->eat();
    }
    atom = stream->eat();
    do
    {
        if (atom.is_token) {
            operation = operation + static_cast<char>(atom.token_val) + " ";
        } else {
            operation = operation + atom.value + " ";
        }
        atom = stream->eat();
    } while (!stream->is_empty());
    Atom function_def = Atom(FUNCTION, formal_parameters, operation, function_name);
    Environment env;
    env.add_symbol(function_name, function_def);
    EnvironmentContainer* container = EnvironmentContainer::getInstance();
    container->push_environment(env);
    return function_def;
}

Atom Parser::eval_function(Atom function, InputStream *stream) {
    vector<Atom> actual_parameters;
    while (!stream->is_empty()) {
        Atom evaluation = evaluate(stream);
        actual_parameters.push_back(evaluation);
    }
    vector<string> formal_parameters = function.formal_parameters;
    string operation = function.operation;
    int index = 0;
    for (string formal_parameter : formal_parameters) {
        operation = regex_replace(operation, regex(formal_parameter), actual_parameters.at(index).value);
        index++;
    }
    Lexer lexer;
    InputStream function_stream = lexer.tokenize_input(operation);
    return evaluate(&function_stream);
}

Atom Parser::cons(InputStream *stream) {
    Atom first_element = evaluate(stream);
    Atom second_element = evaluate(stream);
    string new_list = "(";
    new_list = new_list + first_element.value + " ";
    for (size_t i = 1; i < second_element.value.size(); i++) {
        new_list = new_list + second_element.value.at(i);
    }
    return Atom(LITERAL, new_list);
}

Atom Parser::set(InputStream *stream) {
    string name = stream->eat().value;
    Atom atom = search_for_symbol(name);
    if (atom.token_val == UNDEFINED) {
        return atom;
    }
    Atom evaluation = evaluate(stream);
    EnvironmentContainer* container = EnvironmentContainer::getInstance();
    Environment env;
    env.add_symbol(name, evaluation);
    container->push_environment(env);
    return Atom(SYMBOL, name);
}

Atom Parser::evaluate(InputStream *stream) {
    Atom atom = stream->eat();
    // Base case
    if (atom.is_number) return atom;
    // Start evaluating
    if (atom.token_val == LPAREN) {
        while (atom.token_val != RPAREN) {
            atom = stream->eat();
            if (atom.token_val == PLUS || atom.token_val == MINUS || atom.token_val == MULTIPLY || atom.token_val == DIVIDE) {
                return eval_arithmetic(atom, stream);
            } else if (check_if_boolean(atom)) {
                return eval_boolean(atom, stream);
            } else if (atom.token_val == LPAREN) {
                return evaluate(stream);
            } else if (atom.is_number) {
                return atom;
            } else if (atom.is_symbol) {
                if (atom.value == "define") {
                    return define(stream);
                } else if (atom.value == "set!") {
                    return set(stream);
                } else if (atom.value == "car") {
                    return car(stream);
                } else if (atom.value == "cdr") {
                    return cdr(stream);
                } else if (atom.value == "sqrt") {
                    return my_sqrt(stream);
                } else if (atom.value == "pow") {
                    return my_pow(stream);
                } else if (atom.value == "cons") {
                    return cons(stream);
                } else if (atom.is_literal) {
                    return atom;
                } else if (atom.value == "defun") {
                    return defun(stream);
                } else {
                    if (!search_for_symbol(atom.value).is_function){
                        return search_for_symbol(atom.value);
                    } else {
                        return eval_function(search_for_symbol(atom.value), stream);
                    }
                }
            } else if (atom.is_literal) {
                return atom;
            }
        }
    } else if (atom.is_literal) {
        return atom;
    } else if (atom.token_val == TRUE || atom.token_val == NIL) {
        return atom;
    } else {
        return search_for_symbol(atom.value);
    }
}