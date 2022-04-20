#include <glib.h>

#include "../includes/parser.h"

typedef struct NumVars* T_NumVars; 

struct NumVars {
    GHashTable* map;
    GArray* nums;
};

T_NumVars var_check(T_statement_list root);
void traverse_list(T_statement_list root, GHashTable* map, GArray* list);
void check_loop(T_loop loop, GHashTable* map, GArray* list);
void check_branch(T_branch branch, GHashTable* map, GArray* list);
void check_conditional(T_conditional conditional, GHashTable* map, GArray* list);
void check_statement(T_statement statement, GHashTable* map, GArray* list);
void check_expression(T_expression exp, GHashTable* map, GArray* list);
void checker_error(char* var);