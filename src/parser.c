#include "parser.h"
#include "deep_copy.c"

T_token lookahead_token;

T_token get_lookahead() {
    return lookahead_token;
}

void next_token() {
    // puts("next token");
    lookahead_token = get_token();
    // puts("after lokahead");
}

// T_statement_list parse_statement_list() {
//     if (END != get_lookahead() -> type) {
//         T_statement statement = parse_statement();
//         T_statement_list statement_list = parse_statement_list();
//         return create_statement_list(statement, statement_list);
//     } else {
//         return NULL;
//     }
// }

T_while parse_while() {
    T_token while_token = get_lookahead();
    if (T_WHILE != while_token -> type || WHILE != while_token -> value.t_while -> type)
        parse_error();
    next_token();
    
}

T_conditional parse_conditional() {
    T_token token = get_lookahead();
    if (VAL != token -> type) parse_error();
    T_expression lhs = parse_expression();
    token = get_lookahead();
    if (COMP != token -> type) parse_error();
    T_comp comparator = token -> value.comp -> type;
    next_token();
    T_expression rhs = parse_expression();
    return create_conditional(lhs, comparator, rhs);
}

T_conditional create_conditional(T_expression lhs, T_oper operator, T_expression rhs) {
    T_conditional new_conditional = malloc(sizeof(*new_conditional));
    
}

T_statement parse_statement() {
    T_token token = get_lookahead();
    if (VAL != token -> type || VAR != token -> value.val -> type) parser_error();
    next_token();
    T_token eq = get_lookahead();
    if (COMP != token -> type || EQ != token -> value.comp -> type) parser_error();
    next_token();
    T_expression rhs = parse_expression();
    return create_statement(*(token -> value.val -> value.var), rhs);
}

// T_statement_list create_statement_list(T_statement statement, T_statement_list statement_list) {
//     T_statement_list new_list = malloc(sizeof(*new_list));
//     new_list->statement = statement;
//     new_list->statement_list = statement_list;
//     return new_list;
// }

T_statement create_statement(T_val lhs, T_expression rhs) {
    T_statement new_statement = malloc(sizeof(*new_statement));
    //deep copy lhs
    new_statement -> var = deep_copy_val (lhs);
    //since rhs expression is already heap-allocated, can directly assign reference
    new_statement -> expression = rhs;
    return new_statement;
}



T_expression parse_expression() {
    T_token lhs_token = get_lookahead();
    puts("first");
    if (VAL != lhs_token -> type) parser_error();
    T_val lhs = lhs_token -> value.val;
    // if (lhs -> type == NUM)
    //     printf("%f\n", *(lhs -> value.num));
    // else
    //     printf("%s\n", lhs -> value.var);
    next_token();

    T_token operator_token = get_lookahead();
    if (NL == operator_token -> type || EOF == operator_token -> type) return create_expression(lhs, NULL, NULL);
    puts("second");
    if (OPER != operator_token -> type) parser_error();
    T_oper operator = operator_token -> value.oper;
    next_token();

    T_expression rhs = parse_expression();

    return create_expression(lhs, operator, rhs);
}

T_expression create_expression(T_val lhs, T_oper operator, T_expression rhs) {
    T_expression new_expression = malloc(sizeof(*new_expression));
    new_expression -> lhs = deep_copy_cal(lhs);
    new_expression -> operator = deep_copy_oper(operator);
    new_expression -> rhs = deep_copy_expression(rhs);
    return new_expression;
}

void parser_error(){
    fprintf(stderr, "parser error\n");
    exit(1);
}