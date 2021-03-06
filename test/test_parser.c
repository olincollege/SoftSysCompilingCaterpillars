#include "../includes/static_checker.h"

//gcc -o test_parser parser.c lexer.c lexer.h parser.h test_parser.c && cat test3 | ./test_parser

T_expression test_parse_expression() {
    // printf("x + 5 - 3");
    T_expression exp = parse_expression();
    return exp;
}

T_statement test_parse_statement() {
    // printf("x + 5 - 3");
    return parse_statement();
}

T_loop test_loop_statement() {
    // printf("x + 5 - 3");
    return parse_while();
}

T_conditional test_conditional() {
    // printf("x + 5 - 3");
    return parse_conditional();
}


T_branch test_branch() {
    // printf("x + 5 - 3");
    return parse_branch();
}

void print_expression(T_expression exp) {
    while (exp -> operator != NULL) {
        if (exp -> lhs -> type == NUM)
            printf("%f %d ", *(exp -> lhs -> value.num), (exp -> operator -> type));
        else
            printf("%s %d ", exp -> lhs -> value.var, (exp -> operator -> type));
        exp = exp -> rhs;
    }
    if (exp -> lhs -> type == NUM)
        printf("%f ", *(exp -> lhs -> value.num));
    else
        printf("%s ", exp -> lhs -> value.var);
}

void print_statement(T_statement state) {
    printf("%s ", state -> var -> value.var);
    print_expression(state -> expression);
    puts("");
}

void print_conditional(T_conditional cond) {
    print_expression(cond -> lhs);
    printf("1%d ", cond -> comparator -> type);
    print_expression(cond -> rhs);
    puts("");
}

void print_list(T_statement_list orig_list, int layer) {
    T_statement_list list = orig_list;
    while (1) {
        switch (list -> type) {
            case STATE:
                printf("state %d ", layer);
                print_statement(list -> statement.statement);
                break;
            case BRANCH:
                printf("if %d ", layer);
                print_conditional(list -> statement.branch -> cond);
                print_list(list -> statement.branch -> if_exp, layer + 1);
                if (list -> statement.branch -> else_exp) {
                    printf("else %d \n", layer);
                    print_list(list -> statement.branch -> else_exp, layer + 1);
                }
                printf("endif %d \n", layer);
                break;
            case LOOP:
                printf("while %d ", layer);
                print_conditional(list -> statement.loop -> cond);
                print_list(list -> statement.loop -> exp, layer + 1);
                printf("endwhile %d \n", layer);
        }
        if (list -> statement_list == NULL) break;
        list = list -> statement_list;
    }
}

void print_var(gpointer key, gpointer value, gpointer user_data) {
    fprintf((FILE*) user_data, "%s\n", (char*) key);
}

int main() {
    // puts("inside");
    // next_token();
    // printf("%d \n", get_lookahead() -> type);
    // T_expression exp = test_parse_expression();
    // print_expression(exp);
    
    // T_statement state = test_parse_statement();
    // print_statement(state);

    // T_conditional cond = test_conditional();
    // print_conditional(cond);

    // T_loop loop = test_loop_statement();
    // print_conditional(loop -> cond);
    // print_list(loop -> exp);

    // puts("starting if");
    // T_branch branch = test_branch();
    // print_conditional(branch -> cond);
    // print_list(branch -> if_exp);
    // puts("else");
    // print_list(branch -> else_exp);

    // branch = test_branch();
    // print_conditional(branch -> cond);
    // print_list(branch -> if_exp);
    // if (branch -> else_exp != NULL) {
    //     puts("else");
    //     print_list(branch -> else_exp);
    // }

    T_statement_list program = parse_statement_list(0);
    T_NumVars num_vars = var_check(program);
    GHashTable* vars = num_vars -> map;
    GArray* nums = num_vars -> nums;
    print_list(program, 1);
    FILE *out_file = fopen("var_list.txt", "w");
    g_hash_table_foreach(vars, (GHFunc) print_var, (gpointer) out_file);
    int i = 0;
    for (; i < nums -> len; i++) {
        float num = g_array_index(nums, float, i);
        fprintf(out_file, "%f\n", num);
    }
    // fprintf(out_file, "num: %d\n", nums -> len);
}