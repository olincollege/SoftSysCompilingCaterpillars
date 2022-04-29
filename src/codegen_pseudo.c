#include "../includes/codegen.h" //include header file

//how to run: gcc -o code_gen src/codegen_pseudo.c src/parser.c src/lexer.c src/deep_copy.c src/static_checker.c includes/static_checker.h `pkg-config --libs --cflags glib-2.0` && cat test/test1 | ./code_gen

int directive_num = 1;
int curr_const = 0;

int main(int argc, char *argv[]) {
    char* output_file = "codegen_out.s"; //output an s file
    FILE *out_file = fopen(output_file, "w"); 
    T_statement_list program = parse_statement_list(0); //parse through statement list
    puts("parsed");
    T_NumVars num_vars = var_check(program); //static check
    GHashTable* vars = num_vars -> map;
    GArray* nums = num_vars -> nums;
    declare_vars(out_file, vars); //declare variable
    fprintf(out_file, "main:\n");
    generate_statement_list(out_file, program);
    make_end(out_file);
    declare_constants(out_file, nums);
    puts("Done!");
}

/**
 * 
 * This function iterates through hash table of variables
 * 
 */
void declare_vars(FILE* fptr, GHashTable* vars) { 
    g_hash_table_foreach(vars, (GHFunc) declare_var, (gpointer) fptr);
}

/**
 * 
 * This function prints values from declare_vars
 * 
 */
void declare_var(gpointer key, gpointer value, gpointer user_data) { 
    fprintf((FILE*) user_data, "%s:\n", (char*) key);
    fprintf((FILE*) user_data, "\t.zero\t4\n");
}

/**
 * 
 * This function converts float to hex and hex to int for a constant.
 * 
 */
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

/**
 * @brief A branch consists of a conditional and a statement list. If there is
 * an "else" statement, it also includes another branch nested inside.
 * 
 * This function generates assembly code for a branch
 * 
 */

void generate_branch(FILE *fptr, T_branch branch) { 
    puts("creating branch");
    int else_dir = directive_num++; //move to next directive block for else
    int out_dir = directive_num++; //move to next directive for out 
    puts("created branch");
    generate_conditional(fptr, branch->cond);  
    puts("generated conditional");
    switch (branch->cond->comparator->type) {    
    case 0:
        fprintf(fptr, "\tjne\t"); //arg 1 != arg2
        break;
    case 1:
        fprintf(fptr, "\tjge\t"); //arg2 >= arg1
        break;
    case 2:
        fprintf(fptr, "\tjle\t"); //arg2 <= arg1
        break;
    case 3:
        fprintf(fptr, "\tjeq\t"); //arg1 == arg2
    }
    fprintf(fptr, ".L%d\n", else_dir); //new directive block for else instructions
    generate_statement_list(fptr, branch->if_exp); //generate statement list for if expression
    fprintf(fptr, "\tjmp\t.L%d\n", out_dir); //out of branch
    fprintf(fptr, ".L%d\n", else_dir); //new directive block for else instructions
    generate_statement_list(fptr, branch->else_exp); //generate statement list for else expression
    fprintf(fptr, ".L%d\n", out_dir); //out of branch
}

/**
 * @brief A loop consists of a conditional and the statements within.
 * 
 * This function generates assembly code for those sections.
 * 
 */
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
            fprintf(fptr, "\tjne\t"); //arg 1 != arg2
            break;
        case 1:
            fprintf(fptr, "\tjge\t"); //arg2 >= arg1
            break;
        case 2:
            fprintf(fptr, "\tjle\t"); //arg2 <= arg1
            break;
        case 3:
            fprintf(fptr, "\tjeq\t"); //arg1 == arg2
    }
    fprintf(fptr, ".L%d\n", out_dir); 
    generate_statement_list(fptr, loop->exp); //generate statement list for the expression in the while loop
    fprintf(fptr, "\tjmp\t.L%d\n", head_dir);
}

/**
 * @brief A conditional contains a left hand side, the comparator, and a right hand side.
 * 
 * This function generates assembly code for a conditional.
 * 
 */
void generate_conditional(FILE *fptr, T_conditional cond) {
    puts("generating expressions\n");
    generate_expression(fptr, cond->lhs, 0); //generate expression for left side condition
    generate_expression(fptr, cond->rhs, 1); //generate expression for right side condition
    fprintf(fptr, "\tcomiss\txmm0, xmm1\n"); //compare arg1 and arg2
}

/**
 * @brief An expression contains two operands separated by an operator.
 * 
 * This function generates assembly code for an expression.
 * 
 */
void generate_expression(FILE *fptr, T_expression side, int reg) {
    switch (side->lhs->type) { //left side of expression (num or var)
            case NUM: 
                fprintf(fptr, "\tmovss\txmm%d, DWORD PTR .LC%d[rip]\n", reg, curr_const++);
                break;
            case VAR:
                fprintf(fptr, "\tmovss\txmm%d, DWORD PTR %s[rip]\n", reg, side->lhs->value.var);
    }
    puts("made lhs");
    while (side->rhs != NULL) { //right side of expression
        
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

/**
 * @brief A statement contains a value or variable, an equal sign, and a right hand side.
 * 
 * This function generates assembly code for a statement.
 * 
 */
void generate_statement(FILE *fptr, T_statement statement) { 
    generate_expression(fptr, statement->expression, 0);
    if (statement->var->type == VAR) {
        fprintf(fptr, "\tmovss\tDWORD PTR %s[rip], xmm0\n", statement->var->value.var);
    }
}

/**
 * @brief A statement list consists of a statement, branch, or loop.
 * 
 * This function generates assembly code for a statement list.
 * 
 */
void generate_statement_list(FILE *fptr, T_statement_list sl) { 
    puts("enter generate_statement_list");
    while (sl != NULL && sl->statement_list!=NULL) { //while statement list is not empty, generate
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

/**
 * 
 * This function generates the assembly code to make the end
 * 
 */
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