#include "../includes/codegen.h"

int main(int argc, char *argv[]) {
    char* output_file = "codegen_out.s";
    FILE *out_file = fopen(output_file, "w");
    T_statement_list program = parse_statement_list(0);
    puts("parsed");
    T_NumVars num_vars = var_check(program);
    GHashTable* vars = num_vars -> map;
    GArray* nums = num_vars -> nums;
    declare_vars(out_file, vars);
    declare_constants(out_file, nums);
}

void declare_vars(FILE* fptr, GHashTable* vars) {
    g_hash_table_foreach(vars, (GHFunc) declare_var, (gpointer) fptr);
}

void declare_var(gpointer key, gpointer value, gpointer user_data) {
    fprintf((FILE*) user_data, "%s:\n", (char*) key);
    fprintf((FILE*) user_data, "\t\t.zero\t4\n");
}

void declare_constants(FILE* fptr, GArray* nums) {
    int i = 0;
    double num;
    for (; i < nums -> len; i++) {
        num = g_array_index(nums, float, i);
        fprintf(fptr, ".LC%d:\n", i);
        fprintf(fptr, "\t\t.long\t%a\n", num);
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