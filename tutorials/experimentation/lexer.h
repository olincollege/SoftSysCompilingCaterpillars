#ifndef LEXER_H_
#define LEXER_H_

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct S_token* T_token;

struct S_token {
    enum {VARIABLE, COMPARISON, NUMBER, OPERATOR, SEMICOLON, END} kind;
    union {
        int number;
        char operation;
        char comparison;
        char variable;
    };
};

T_token lex();

void lexer_error();

T_token create_end_token();
T_token create_semicolon_token();
T_token create_number_token(char c);
T_token create_operator_token(char c);
T_token create_variable_token(char c);
T_token create_comparison_token(char c);

#endif