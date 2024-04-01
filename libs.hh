#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <stdio.h>

using namespace std;

enum Tokens {
    PLUS = '+',
    MINUS = '-',
    MULTIPLY = '*',
    DIVIDE = '/',
    LPAREN = '(',
    RPAREN = ')',
    SPACE = ' ',
    TRUE = 'T',
    FALSE = 'F',
    EMPTY = '_',
    LITERAL = 1,
    SYMBOL = 2,
    KEYWORD = 3,
    VARIABLE = 4,
    FUNCTION = 5,
    TOKEN = 0
};