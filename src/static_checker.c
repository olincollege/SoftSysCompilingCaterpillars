#include "../includes/static_checker.h"


T_NumVars var_check(T_statement_list root) {
    guint i;
    gchar *contents = NULL;
    gboolean ret;
    gpointer key;
    GHashTable* map = g_hash_table_new(g_str_hash, g_str_equal);
    GArray* nums = g_array_new(FALSE, FALSE, sizeof(double));
    traverse_list(root, map, nums);
    T_NumVars num_vars = malloc(sizeof(T_NumVars));
    num_vars -> map = map;
    num_vars -> nums = nums;
    return num_vars;
}

void traverse_list(T_statement_list root, GHashTable* map, GArray* list) {
    if (root == NULL) return;
    if (root -> type == STATE) {
        check_statement(root -> statement.statement, map, list);
    } else if (root -> type == LOOP) {
        check_loop(root -> statement.loop, map, list);
    } else {
        check_branch(root -> statement.branch, map, list);
    }
    traverse_list (root -> statement_list, map, list);
}

void check_loop(T_loop loop, GHashTable* map, GArray* list) {
    check_conditional(loop -> cond, map, list);
    traverse_list(loop -> exp, map, list);
}

void check_branch(T_branch branch, GHashTable* map, GArray* list) {
    check_conditional(branch -> cond, map, list);
    traverse_list(branch -> if_exp, map, list);
    traverse_list(branch -> else_exp, map, list);
}

void check_conditional(T_conditional conditional, GHashTable* map, GArray* list) {
    check_expression(conditional -> lhs, map, list);
    check_expression(conditional -> rhs, map, list);
}

void check_statement(T_statement statement, GHashTable* map, GArray* list) {
    //make sure no undeclared variables are used before. If they are, there will
    //be an error and the insertion won't work
    check_expression(statement -> expression, map, list);
    //will do nothing if already exists, otherwise add
    g_hash_table_insert(map, (gpointer) (statement -> var -> value.var), NULL);
}

void check_expression(T_expression exp, GHashTable* map, GArray* list) {
    if (exp -> lhs -> type == VAR) {
        if (!g_hash_table_contains (map, (void*) exp -> lhs -> value.var)) {
                checker_error(exp -> lhs -> value.var);
        }
    } else {
        list = g_array_append_vals(list, (void*) exp -> lhs -> value.num, 1);
    }
    if (exp -> rhs) {
        check_expression(exp -> rhs, map, list);
    }
}

/**
 * @brief Raises error if checker fails
 * 
 */
void checker_error(char* var){
    fprintf(stderr, "%s used before declared\n", var);
    exit(1);
}

