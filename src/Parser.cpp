#include "../headers/Parser.hh"

void Parser::parse(TokenStream tokens) {
    if (tokens.is_empty()) return;
    Token evaluation = evaluate(&tokens);
    if (evaluation.token_val == ERROR) {puts("ERROR: Error Token Returned"); return;}
    cout << evaluation.data_val << endl;
}

Token Parser::eval_arithmetic(TokenStream *tokens, Token token) {
    switch (token.token_val) {
        case PLUS: {
            int operand1 = stoi(evaluate(tokens).data_val);
            int operand2 = stoi(evaluate(tokens).data_val);
            token = tokens->eat();
            if (token.token_val == RPAREN) {
                return Token(to_string(operand1 + operand2), LITERAL);
            } else {
                tokens->push_front(token);
                tokens->push_front(Token(to_string(operand1 + operand2), LITERAL));
                tokens->push_front(Token(PLUS));
                tokens->push_front(Token(LPAREN));
                return evaluate(tokens);
            }
            break;
        }
        case MINUS: {
            int operand1 = stoi(evaluate(tokens).data_val);
            int operand2 = stoi(evaluate(tokens).data_val);
            token = tokens->eat();
            if (token.token_val == RPAREN) {
                return Token(to_string(operand1 - operand2), LITERAL);
            } else {
                tokens->push_front(token);
                tokens->push_front(Token(to_string(operand1 - operand2), LITERAL));
                tokens->push_front(Token(MINUS));
                tokens->push_front(Token(LPAREN));
                return evaluate(tokens);
            }
            break;
        }
        case MULTIPLY: {
            int operand1 = stoi(evaluate(tokens).data_val);
            int operand2 = stoi(evaluate(tokens).data_val);
            token = tokens->eat();
            if (token.token_val == RPAREN) {
                return Token(to_string(operand1 * operand2), LITERAL);
            } else {
                tokens->push_front(token);
                tokens->push_front(Token(to_string(operand1 * operand2), LITERAL));
                tokens->push_front(Token(MULTIPLY));
                tokens->push_front(Token(LPAREN));
                return evaluate(tokens);
            }
            break;
        }
        case DIVIDE: {
            int operand1 = stoi(evaluate(tokens).data_val);
            int operand2 = stoi(evaluate(tokens).data_val);
            if (operand2 == 0) {
                puts("ERROR: Attempted division by 0");
                return Token(ERROR);
            }
            token = tokens->eat();
            if (token.token_val == RPAREN) {
                return Token(to_string(operand1 / operand2), LITERAL);
            } else {
                tokens->push_front(token);
                tokens->push_front(Token(to_string(operand1 / operand2), LITERAL));
                tokens->push_front(Token(DIVIDE));
                tokens->push_front(Token(LPAREN));
                return evaluate(tokens);
            }
            break;
        }
        case LPAREN: {
            tokens->push_front(evaluate(tokens));
            break;
        }
    }
    return Token(ERROR);
}

Token Parser::eval_keyword(TokenStream *tokens, Token token) {
    if (token.data_val == "define") {

    } else if (token.data_val == "defun") {

    } else {

    }
    return Token(ERROR);
}

Token Parser::evaluate(TokenStream *tokens) {
    Token token = tokens->eat();
    if (token.is_literal) return token;
    if (token.token_val == LPAREN) {
        while (token.token_val != RPAREN) {
            token = tokens->eat();
            if (token.token_val == PLUS or token.token_val == MINUS or token.token_val == MULTIPLY or token.token_val == DIVIDE) 
                return eval_arithmetic(tokens, token);
            else if (token.is_keyword) {
                
            }
            
        }
    }
    return Token(ERROR);
}