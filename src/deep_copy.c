#include "parser.h"

T_val deep_copy_val(T_val val) {
    T_val copied_val = malloc(sizeof(*copied_val));
    if (val -> type == NUM) {
        copied_val -> type = NUM;
        copied_val -> value.num = malloc(*(copied_val -> value.num));
        *(copied_val -> value.num) = *(val -> value.num);
    } else {
        copied_val -> type = VAR;
        //+1 to include \n
        copied_val -> value.var = malloc(strlen(val -> value.var) + 1);
        strcpy(copied_val -> value.var, val -> value.var);
    }
    return copied_val;
}

T_oper deep_copy_oper(T_oper oper) {
    T_oper copied_oper = malloc(sizeof(*copied_oper));
    copied_oper -> type = oper -> type;
    return copied_oper;
}

T_comp deep_copy_comp(T_comp comp) {
    T_comp copied_comp = malloc(sizeof(*copied_comp));
    copied_comp -> type = comp -> type;
    return copied_comp;
}

T_expression deep_copy_expression(T_expression expression) {
    T_expression copied_expression = malloc(sizeof(*copied_expression));
    copied_expression -> lhs = deep_copy_val(expression -> lhs);
    copied_expression -> operator = deep_copy_oper(expression -> operator);
    if (expression -> rhs == NULL)
        copied_expression -> rhs = NULL;
    else
        copied_expression -> rhs = deep_copy_expression(expression -> rhs);

    return copied_expression;
}

T_statement deep_copy_statement(T_statement statement) {
    T_statement copied_statement = malloc(sizeof(*copied_statement));
    copied_statement -> var = deep_copy_val (statement -> var);
    copied_statement -> expression = deep_copy_expression(statement -> expression);
    return copied_statement;
}