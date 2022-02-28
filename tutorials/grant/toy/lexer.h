#ifndef LEXER_H_
#define LEXER_H_

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct S_token* T_token;

struct S_token {
    enum {NUMBER, OPERATOR, SEMICOLON, END} kind;
    union {
        int number;
        char character;
    };
};

T_token lex();

void lexer_error();

T_token create_end_token();
T_token create_semicolon_token();
T_token create_number_token();
T_token create_operator_token();

#endif