#include "../includes/static_checker.h"

typedef struct S_loop_wd* T_loop_wd;
typedef struct S_branch_wd* T_branch_wd;

struct S_loop_wd {
    T_loop loop;
    int head_dir;
    int end_dir;
};

struct S_branch_wd {
    T_branch branch;
    int else_dir;
    int out_dir;
};

void declare_vars(FILE* fptr, GHashTable* vars);
void declare_var(gpointer key, gpointer value, gpointer user_data);
void declare_constants(FILE* fptr, GArray* nums);
void generate_branch(FILE *fptr, T_branch branch);
void generate_while(FILE *fptr, T_loop loop);
void generate_conditional(FILE *fptr, T_conditional cond);
void generate_expression(FILE *fptr, T_expression side, int reg);
void generate_statement(FILE *fptr, T_statement statement);
void generate_statement_list(FILE *fptr, T_statement_list sl);
void make_start(FILE *fptr);
void make_end(FILE *fptr);
T_loop_wd create_loop_wd(T_loop loop);
T_branch_wd create_branch_wd(T_branch branch);
