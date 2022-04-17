#include <glib.h>

#include "../includes/parser.h"

int var_check(T_statement_list root);
void traverse_list(T_statement_list root, GHashTable* map);
void check_loop(T_loop loop, GHashTable* map);
void check_branch(T_branch branch, GHashTable* map);
void check_conditional(T_conditional conditional, GHashTable* map);
void check_statement(T_statement statement, GHashTable* map);
void check_expression(T_expression exp, GHashTable* map);
void checker_error(char* var);