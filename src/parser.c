#include "parser.h"

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

// T_statement parse_statement() {
//     T_expression expression = parse_expression();
//     T_token semicolon = get_lookahead();
//     if (NL != semicolon -> type) {
//         parser_error();
//     }
//     next_token();
//     return create_statement(expression);
// }

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

// T_statement_list create_statement_list(T_statement statement, T_statement_list statement_list) {
//     T_statement_list new_list = malloc(sizeof(*new_list));
//     new_list->statement = statement;
//     new_list->statement_list = statement_list;
//     return new_list;
// }

// T_statement create_statement(T_expression expression) {
//     T_statement new_statement = malloc(sizeof(*new_statement));
//     new_statement->expression = expression;
//     return new_statement;
// }

T_expression create_expression(T_val lhs, T_oper operator, T_expression rhs) {
    T_expression new_expression = malloc(sizeof(*new_expression));
    new_expression -> lhs = lhs;
    new_expression -> operator = operator;
    new_expression -> rhs = rhs;
    return new_expression;
}

void parser_error(){
    fprintf(stderr, "parser error\n");
    exit(1);
}