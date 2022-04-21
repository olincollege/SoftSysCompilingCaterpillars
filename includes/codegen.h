#include "../includes/static_checker.h"
// #include "../includes/deep_copy.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct S_loop_wd* T_loop_wd;
typedef struct S_branch_wd* T_branch_wd;

struct S_loop_wd {
    T_loop loop;
    int head_dir;
};

struct S_branch_wd {
    T_branch branch;
    int else_dir;
};

void declare_vars(FILE* fptr, GHashTable* vars);
void declare_var(gpointer key, gpointer value, gpointer user_data);
void declare_constants(FILE* fptr, GArray* nums);