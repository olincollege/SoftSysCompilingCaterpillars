#include "../includes/codegen.h"

//how to run: gcc -o code_gen src/codegen_pseudo.c src/parser.c src/lexer.c src/deep_copy.c src/static_checker.c includes/static_checker.h `pkg-config --libs --cflags glib-2.0` && cat test/test1 | ./code_gen

int directive_num = 1;
int curr_const = 0;

int main(int argc, char *argv[]) {
    char* output_file = "codegen_out.s";
    FILE *out_file = fopen(output_file, "w");
    T_statement_list program = parse_statement_list(0);
    puts("parsed");
    T_NumVars num_vars = var_check(program);
    GHashTable* vars = num_vars -> map;
    GArray* nums = num_vars -> nums;
    declare_vars(out_file, vars);
    fprintf(out_file, "main:\n");
    generate_statement_list(out_file, program);
    make_end(out_file);
    declare_constants(out_file, nums);
    puts("Done!");
}

void declare_vars(FILE* fptr, GHashTable* vars) {
    g_hash_table_foreach(vars, (GHFunc) declare_var, (gpointer) fptr);
}

void declare_var(gpointer key, gpointer value, gpointer user_data) {
    fprintf((FILE*) user_data, "%s:\n", (char*) key);
    fprintf((FILE*) user_data, "\t.zero\t4\n");
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
        // fprintf(fptr, "\t.long\t%ld\n", strtol(hex, NULL, 10));
        fprintf(fptr, "\t.long\t%d\n", (int)strtol(hex, NULL, 0));
    }
}

void generate_branch(FILE *fptr, T_branch branch) {
    puts("creating branch");
    // T_branch_wd branch_wd = create_branch_wd(branch);
    int else_dir = directive_num++;
    int out_dir = directive_num++;
    puts("created branch");
    generate_conditional(fptr, branch->cond);
    puts("generated conditional");
    switch (branch->cond->comparator->type) {    
    case 0:
        fprintf(fptr, "\tjne\t");
        break;
    case 1:
        fprintf(fptr, "\tjge\t");
        break;
    case 2:
        fprintf(fptr, "\tjle\t");
        break;
    case 3:
        fprintf(fptr, "\tjeq\t");
    }
    fprintf(fptr, ".L%d\n", else_dir);
    generate_statement_list(fptr, branch->if_exp);
    fprintf(fptr, "\tjmp\t.L%d\n", out_dir);
    fprintf(fptr, ".L%d\n", else_dir);
    generate_statement_list(fptr, branch->else_exp);
    fprintf(fptr, ".L%d\n", out_dir);
}

void generate_while(FILE *fptr, T_loop loop) {
    puts("generating while");
    int head_dir = directive_num++;
    int out_dir = directive_num++;
    puts("generated while");
    fprintf(fptr, ".L%d:\n",head_dir);
    puts("going to make conditional");
    generate_conditional(fptr, loop->cond);
    puts("made conditional");
    switch (loop->cond->comparator->type) {
        case 0:
            fprintf(fptr, "\tjne\t");
            break;
        case 1:
            fprintf(fptr, "\tjge\t");
            break;
        case 2:
            fprintf(fptr, "\tjle\t");
            break;
        case 3:
            fprintf(fptr, "\tjeq\t");
    }
    fprintf(fptr, ".L%d\n", out_dir);
    generate_statement_list(fptr, loop->exp);
    fprintf(fptr, "\tjmp\t.L%d\n", head_dir);
}

void generate_conditional(FILE *fptr, T_conditional cond) {
    puts("generating expressions\n");
    generate_expression(fptr, cond->lhs, 0);
    generate_expression(fptr, cond->rhs, 1);
    fprintf(fptr, "\tcomiss\txmm0, xmm1\n");
}

void generate_expression(FILE *fptr, T_expression side, int reg) {
    switch (side->lhs->type) {
            case NUM:
                fprintf(fptr, "\tmovss\txmm%d, DWORD PTR .LC%d[rip]\n", reg, curr_const++);
                break;
            case VAR:
                fprintf(fptr, "\tmovss\txmm%d, DWORD PTR %s[rip]\n", reg, side->lhs->value.var);
    }
    puts("made lhs");
    while (side->rhs != NULL) {
        
        switch (side->rhs->lhs->type) {
            case NUM:
                fprintf(fptr, "\tmovss\txmm%d, DWORD PTR .LC%d[rip]\n", reg + 1, curr_const++);
                break;
            case VAR:
                fprintf(fptr, "\tmovss\txmm%d, DWORD PTR %s[rip]\n", reg + 1, side->rhs->lhs->value.var);
        }
        switch(side->operator->type) {
            case ADD:
                fprintf(fptr, "\taddss\t");
                break;
            case SUB:
                fprintf(fptr, "\tsubss\t");
                break;
            case MULT:
                fprintf(fptr, "\tmulss\t");
                break;
            case DIV:
                fprintf(fptr, "\tdivss\t");
        }
        fprintf(fptr, "xmm%d, xmm%d\n", reg, reg + 1);
        side = side->rhs;
    }
}

void generate_statement(FILE *fptr, T_statement statement) {
    generate_expression(fptr, statement->expression, 0);
    if (statement->var->type == VAR) {
        fprintf(fptr, "\tmovss\tDWORD PTR %s[rip], xmm0\n", statement->var->value.var);
    }
}

void generate_statement_list(FILE *fptr, T_statement_list sl) {
    puts("enter generate_statement_list");
    while (sl != NULL && sl->statement_list!=NULL) {
        puts("making list");
        switch(sl->type) {
            case STATE:
                generate_statement(fptr, sl->statement.statement);
                break;
            case BRANCH:
                puts("sl to branch gen");
                generate_branch(fptr, sl->statement.branch);
                break;
            case LOOP:
                generate_while(fptr, sl->statement.loop);
        }
        sl = sl->statement_list;
    }
    puts("final statement");
    if (sl != NULL) {
        switch(sl->type) {
            case STATE:
                generate_statement(fptr, sl->statement.statement);
                break;
            case BRANCH:
                generate_branch(fptr, sl->statement.branch);
                break;
            case LOOP:
                generate_while(fptr, sl->statement.loop);
        }
    }
}

void make_end(FILE *fptr) {
    fprintf(fptr, ".L%d:\n", directive_num);
    fprintf(fptr, "\tnop\n\tmov eax, 0\n\tpop rbp\n\tret\n");
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