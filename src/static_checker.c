#include "../includes/static_checker.h"


int var_check(T_statement_list root) {
    guint i;
    gchar *contents = NULL;
    gboolean ret;
    gpointer key;
    GList* values;
    GHashTable* map = g_hash_table_new(g_str_hash, g_str_equal);
    traverse_list(root, map);
}

void traverse_list(T_statement_list root, GHashTable* map) {
    if (root == NULL) return;
    if (root -> type == STATE) {
        check_statement(root -> statement.statement, map);
    } else if (root -> type == LOOP) {
        check_loop(root -> statement.loop, map);
    } else {
        check_branch(root -> statement.branch, map);
    }
    traverse_list (root -> statement_list, map);
}

void check_loop(T_loop loop, GHashTable* map) {
    check_conditional(loop -> cond, map);
    traverse_list(loop -> exp, map);
}

void check_branch(T_branch branch, GHashTable* map) {
    check_conditional(branch -> cond, map);
    traverse_list(branch -> if_exp, map);
    traverse_list(branch -> else_exp, map);
}

void check_conditional(T_conditional conditional, GHashTable* map) {
    check_expression(conditional -> lhs, map);
    check_expression(conditional -> rhs, map);
}

void check_statement(T_statement statement, GHashTable* map) {
    //make sure no undeclared variables are used before. If they are, there will
    //be an error and the insertion won't work
    check_expression(statement -> expression, map);
    //will do nothing if already exists, otherwise add
    g_hash_table_insert(map, (gpointer) (statement -> var -> value.var), NULL);
}

void check_expression(T_expression exp, GHashTable* map) {
    if (exp -> lhs -> type == VAR) {
        puts(exp -> lhs -> value.var);
        if (!g_hash_table_contains (map, (void*) exp -> lhs -> value.var)) {
                checker_error(exp -> lhs -> value.var);
        }
    }
    if (exp -> rhs) {
        check_expression(exp -> rhs, map);
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

