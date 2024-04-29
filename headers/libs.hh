// Header file that contains helpful libraries as well as Token definitions

#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <cmath>
#include <stdio.h>
#include <regex>
#include <fstream>
#include <limits>

using namespace std;

// Enum that contains the values of different Token/Atom values that the program needs to use
enum Tokens {
    PLUS = '+',
    MINUS = '-',
    MULTIPLY = '*',
    DIVIDE = '/',
    LPAREN = '(',
    RPAREN = ')',
    QUOTE = '\'',
    SPACE = ' ',
    TRUE = 'T',
    NIL = '~',
    LESS_THAN = '<',
    LESS_THAN_EQUAL = '}',
    GREATER_THAN = '>',
    GREATER_THAN_EQUAL = '{',
    EQUAL = '=',
    NOT_EQUAL = 'N',
    NOT = '!',
    AND = '&',
    OR = '|',
    IF = 'I',
    EMPTY = '_',
    ERROR = '%',
    UNDEFINED = '$',
    NUMBER = 1,
    SYMBOL = 2,
    LITERAL = 3,
    FUNCTION = 4,
    TOKEN = 0
};