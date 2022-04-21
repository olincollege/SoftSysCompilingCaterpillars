#include "../includes/static_checker.h"
// #include "../includes/deep_copy.h"
#include <stdio.h>
#include <stdlib.h>

void declare_vars(FILE* fptr, GHashTable* vars);
void declare_var(gpointer key, gpointer value, gpointer user_data);
void declare_constants(FILE* fptr, GArray* nums);