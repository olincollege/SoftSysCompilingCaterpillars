#include "../includes/codegen.h"

//how to run: gcc -o code_gen src/codegen_pseudo.c src/parser.c src/lexer.c src/deep_copy.c src/static_checker.c includes/static_checker.h `pkg-config --libs --cflags glib-2.0` && cat test/test3 | ./code_gen

int directive_num = 1;
int curr_const = 1;

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
    float num;
    for (; i < nums -> len; i++) {
        num = g_array_index(nums, float, i);
        //convert float to hex, then hex to int
        char hex[20];
        snprintf(hex, sizeof(hex), "0x%x", *(unsigned int*)&num);
        fprintf(fptr, ".LC%d:\n", i);
        // fprintf(fptr, "\t\t.long\t%ld\n", strtol(hex, NULL, 10));
        fprintf(fptr, "\t\t.long\t%d\n", (int)strtol(hex, NULL, 0));
    }
}

void generate_branch(FILE *fptr, T_branch branch) {
    T_branch_wd branch_wd = create_branch_wd(branch);
    generate_conditional(fptr, branch_wd->branch->cond);
    switch (branch_wd->branch->cond->comparator->type) {
    case 0:
        fprint(fptr, "\t\tjne\t\t");
        break;
    case 1:
        fprint(fptr, "\t\tjge\t\t");
        break;
    case 2:
        fprint(fptr, "\t\tjle\t\t");
        break;
    case 3:
        fprint(fptr, "\t\tjeq\t\t");
    }
    fprintf(fptr, ".L%d\n", branch_wd->else_dir);
    generate_statement_list(branch_wd->branch->if_exp);
    fprintf(fptr, ".L%d\n", branch_wd->else_dir);
    generate_statement_list(branch_wd->branch->else_exp);
    fprintf(fptr, ".L%d\n", branch_wd->out_dir);
}

void generate_while(FILE *fptr, T_loop loop) {
    T_loop_wd loop_wd = create_loop_wd(loop);
    fprintf(fptr, ".L%d:\n",directive_num++);
    generate_conditional(fptr, loop_wd->loop->cond);
    switch (loop_wd->loop->cond->comparator->type) {
        case 0:
            fprint(fptr, "\t\tjne\t\t");
            break;
        case 1:
            fprint(fptr, "\t\tjge\t\t");
            break;
        case 2:
            fprint(fptr, "\t\tjle\t\t");
            break;
        case 3:
            fprint(fptr, "\t\tjeq\t\t");
    }
    fprintf(fptr, ".L%d\n", loop_wd->end_dir);
    generate_statement_list(loop_wd->loop->exp);
    fprintf(fptr, "\t\tjmp\t\t.L%d\n", loop_wd->head_dir);
}

void generate_conditional(FILE *fptr, T_conditional cond) {
    generate_expression(cond->lhs, 0);
    generate_expression(cond->rhs, 1);
    fprintf(fptr, "\t\tcomiss\nxmm0, xmm1\n");
}

void generate_expression(T_expression side, int reg) {
    if (side->rhs == NULL) {
        switch (side->lhs->type) {
            case 0:
                fprintf(fptr, "\t\tmovss\txmm%d, DWORD PTR .LC%d[rip]", reg, curr_const++);
                break;
            case 1:
                fprintf(fptr, "\t\tmovss\txmm%d, DWORD PTR %s[rip]", reg, side->lhs->value);
        }
    } else {
        generate_expression(side->rhs, reg + 1);
    }
}


T_loop_wd create_loop_wd(T_loop loop) {
    T_loop_wd new_loop = malloc(sizeof(*new_loop));
    new_loop -> loop = loop;
    new_loop -> head_dir = directive_num++;
    new_loop -> end_dir = directive_num++;
}

T_branch_wd create_branch_wd(T_branch branch) {
    T_branch_wd new_branch = malloc(sizeof(*new_branch));
    new_branch ->branch = branch;
    new_branch ->else_dir = directive_num++;
    new_branch ->out_dir = directive_num++;
}