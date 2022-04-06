#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

#include "../includes/parser.h"

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

}

void check_conditional(T_conditional conditional, GHashTable* map) {

}

void check_expression(T_expression exp, GHashTable* map) {
    if (exp -> lhs -> type == VAR) {
            if (!g_hash_table_contains (map, (void*) exp -> lhs -> value.var)) {
                parser_error(exp -> lhs -> value.var);
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
void parser_error(char* var){
    fprintf(stderr, "%s used before declared\n");
    exit(1);
}

int main() {
    printf("hello world");
}

