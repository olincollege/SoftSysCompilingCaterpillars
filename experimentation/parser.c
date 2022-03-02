#include "parser.h"

T_token lookahead_token;

T_token get_lookahead() {
    return lookahead_token;
}

void next_token() {
    lookahead_token = lex();
}

T_statement_list parse_statement_list() {
    if (END != get_lookahead() -> kind) {
        T_statement statement = parse_statement();
        T_statement_list statement_list = parse_statement_list();
        return create_statement_list(statement, statement_list);
    } else {
        return NULL;
    }
}

T_statement parse_statement() {
    T_expression expression = parse_expression();
    T_token semicolon = get_lookahead();
    if (SEMICOLON != semicolon -> kind) {
        parser_error();
    }
    next_token();
    return create_statement(expression);
}

T_expression parse_expression() {
    T_token operand1 = get_lookahead();
    if (NUMBER != operand1 -> kind) parser_error();
    next_token();

    T_token operator = get_lookahead();
    if (OPERATOR != operator -> kind) parser_error();
    next_token();

    T_token operand2 = get_lookahead();
    if (NUMBER != operand2 -> kind) parser_error();
    next_token();

    return create_expression(operand1, operator, operand2);
}

T_statement_list create_statement_list(T_statement statement, T_statement_list statement_list) {
    T_statement_list new_list = malloc(sizeof(*new_list));
    new_list->statement = statement;
    new_list->statement_list = statement_list;
    return new_list;
}

T_statement create_statement(T_expression expression) {
    T_statement new_statement = malloc(sizeof(*new_statement));
    new_statement->expression = expression;
    return new_statement;
}

T_expression create_expression(T_token operand1, T_token operator, T_token operand2) {
    T_expression new_expression = malloc(sizeof(*new_expression));
    new_expression -> operand1 = operand1;
    new_expression -> operator = operator;
    new_expression -> operand2 = operand2;
    return new_expression;
}

void parser_error(){
    fprintf(stderr, "parser error\n");
    exit(1);
}