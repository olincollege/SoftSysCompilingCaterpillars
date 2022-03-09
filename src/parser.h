#ifndef PARSER_H_
#define PARSER_H_

#include <stdlib.h>

#include "lexer.h"

typedef struct S_statement_list* T_statement_list; // T_statement_list is a pointer to a struct S_statement_list
typedef struct S_statement* T_statement;
typedef struct S_branch* T_branch;
typedef struct S_while* T_while;
typedef struct S_conditional* T_conditional;
typedef struct S_expression* T_expression;

struct S_statement_list {
    union statements {
        T_statement statement;
        T_branch branch;
        T_while loop;
    } statement;
    T_statement_list statement_list;
};

struct S_statement {
    T_val var;
    T_expression expression;
};

struct S_branch {
    T_conditional cond;
    T_statement_list if_exp;
    T_statement_list else_exp;
};

struct S_while {
    T_conditional cond;
    T_statement_list exp;
};

struct S_conditional {
    T_expression lhs;
    T_oper comparator;
    T_expression rhs;
};

struct S_expression {
    T_val lhs;
    T_oper operator;
    T_expression rhs;
};

T_statement_list parse_statement_list();
T_statement parse_statement();
T_expression parse_expression();

T_statement_list create_statement_list(T_statement statement, T_statement_list statement_list);
// T_statement create_statement(T_expression expression);
// T_expression create_expression(T_token operand1, T_token operator, T_token operand2);

T_token get_lookahead();
void next_token();

void parser_error();

#endif