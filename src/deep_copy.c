#include "deep_copy.h"
#include <string.h>

// A deep copy copies all the elements of an object. 
// It is created in scenarios where a new copy is made without refering to the original data. 

T_val deep_copy_val(T_val val) {
    if (val == NULL) return NULL;
    T_val copied_val = malloc(sizeof(*copied_val));
    if (val -> type == NUM) {
        copied_val -> type = NUM;
        copied_val -> value.num = malloc(sizeof(*(copied_val -> value.num)));
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
    if (oper == NULL) return NULL;
    T_oper copied_oper = malloc(sizeof(*copied_oper));
    copied_oper -> type = oper -> type;
    return copied_oper;
}

T_comp deep_copy_comp(T_comp comp) {
    if (comp == NULL) return NULL;
    T_comp copied_comp = malloc(sizeof(*copied_comp));
    copied_comp -> type = comp -> type;
    return copied_comp;
}

T_expression deep_copy_expression(T_expression expression) {
    if (expression == NULL) return NULL;
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
    if (statement == NULL) return NULL;
    T_statement copied_statement = malloc(sizeof(*copied_statement));
    copied_statement -> var = deep_copy_val (statement -> var);
    copied_statement -> expression = deep_copy_expression(statement -> expression);
    return copied_statement;
}

T_conditional deep_copy_conditional(T_conditional conditional) {
    if (conditional == NULL) return NULL;
    T_conditional copied_conditional = malloc(sizeof(*copied_conditional));
    copied_conditional -> lhs = deep_copy_expression(conditional -> lhs);
    copied_conditional -> comparator = deep_copy_comp(conditional -> comparator);
    copied_conditional -> rhs = deep_copy_expression(conditional -> rhs);
    return copied_conditional;
}

T_statement_list deep_copy_list(T_statement_list list) {
    if (list == NULL) return NULL;
    T_statement_list copied_list;
    T_statement_list cur_list = copied_list;
    while (list != NULL) {
        cur_list = malloc(sizeof(*cur_list));
        if (cur_list -> type == STATE) {
            cur_list -> type = STATE;
            cur_list -> statement.statement = deep_copy_statement(list -> statement.statement);
        }
        // else if (cur_list -> type == BRANCH) 
        //     cur_list -> statement.branch = deep_copy_branch(list -> statement.branch);
        // else
        //     cur_list -> statement.loop = deep_copy_statement(list ->
        //     statement.loop);
        cur_list = cur_list -> statement_list;
        list = list -> statement_list;
    }
    return copied_list;
}