#ifndef PARSER_H_
#define PARSER_H_

#include <stdlib.h>
#include <stdio.h>

#include "lexer.h"


typedef struct S_statement_list* T_statement_list; // T_statement_list is a pointer to a struct S_statement_list
typedef struct S_statement* T_statement;
typedef struct S_branch* T_branch;
typedef struct S_loop* T_loop;
typedef struct S_conditional* T_conditional;
typedef struct S_expression* T_expression;

struct S_statement_list { //contains a statement and next list
    enum {STATE, BRANCH, LOOP} type;
    union statements {
        T_statement statement;
        T_branch branch;
        T_loop loop;
    } statement;
    T_statement_list statement_list;
};

struct S_statement { //contains an expression
    T_val var;
    T_expression expression;
};

struct S_branch { //for conditionals
//                branch 
//           /      |       \
//          /       |        \
//condition     if statement     else statement
    T_conditional cond;
    T_statement_list if_exp;
    T_statement_list else_exp;
};

struct S_loop { //for while loops
    T_conditional cond;
    T_statement_list exp;
};

struct S_conditional { //for conditions (lhs (left hand side) expression + comparator + rhs (right hand side) expression)
    T_expression lhs;
    T_comp comparator;
    T_expression rhs;
};

struct S_expression { //for statements (expression = lhs operand + operator + rhs operand)
    T_val lhs;
    T_oper operator;
    T_expression rhs;
};

//parse through the lexed input
T_statement_list parse_statement_list(int in_loop_while);
T_statement parse_statement();
T_expression parse_expression();
T_conditional parse_conditional();
T_loop parse_while();
T_branch parse_branch();
T_token get_token();


//create output based on parsed input
T_statement_list create_statement_list(int type, T_statement statement, T_statement_list statement_list);
T_statement create_statement(T_val lhs, T_expression rhs);
T_expression create_expression(T_val lhs, T_oper operator, T_expression rhs);
T_conditional create_conditional(T_expression lhs, T_comp comparator, T_expression rhs);
T_loop create_while(T_conditional conditional, T_statement_list list);
T_branch create_branch(T_conditional conditional, T_statement_list if_statements, T_statement_list else_statements);
void print_expression(T_expression exp);
void print_statement(T_statement state);
void print_conditional(T_conditional cond);
T_token get_lookahead();
void next_token();

void parser_error();

#endif 