#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>

#include "lexer.h"

typedef struct S_statement_list* T_statement_list;
typedef struct S_statement* T_statement;
typedef struct S_expression* T_expression;

struct S_statement_list{
    T_statement statement;
    T_statement_list statement_list;
};

struct S_statement {
    T_expression expression;
};

struct S_expresion {
    T_token operand1;
    T_token operator;
    T_token operand2; 
};

T_statement_list parse_statement_list();
T_statement parse_statement();
T_expression parse_expression();

T_statement_list create_statement_list(T_statement statement, T_statement_list statement_list);
T_statemet create_statement(T_expression expression);
T_expression create_expression(T_token operand1, T_token operator, T_token operand2);

T_token get_lookahead();
void next_token();

void parser_error();

#endif
