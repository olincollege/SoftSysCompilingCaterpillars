#include "../includes/parser.h"
#include "../includes/deep_copy.h"
//#include "../includes/codegen.h"
#include <stdio.h>
#include <stdlib.h>

int directive_num = 1;

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

int main(int argc, char *argv[]) {
    FILE *fptr = fopen("codegen_out.s", "w");
    /*make char array of vars*/
    char **all_vars;
    int all_vars_count;

    /*add variables*/
    declare_vars(fptr, all_vars, all_vars_count);

    // Create main section
    fprintf(fptr, "main:\n\t\tpush\trbp\n\t\tmov\t\trbp, rsp\n");
}

void declare_vars(FILE *fptr, char *vars[], int count) {
    for (int i = 0; i < count; i++) {
        fprintf(fptr, "%s:\n", vars[i]);
        fprintf(fptr, "\t\t.zero\t4\n");
    }
}

void generate_while(FILE *fptr, T_loop loop) {
    fprintf(".L%d:\n",directive_num++);
    generate_conditional(loop->cond);

}



T_loop_wd create_loop_wd(T_loop loop) {
    T_loop_wd new_loop = malloc(sizeof(*new_loop));
    new_loop -> loop = loop;
    new_loop -> head_dir = directive_num;
}

T_branch_wd create_branch_wd(T_branch branch) {
    T_branch_wd new_branch = malloc(sizeof(*new_branch));
    new_branch ->branch = branch;
    new_branch ->else_dir = directive_num++;
}