#include "codegen.h"

void gencode_statment_list(T_statement_list statement_list) {
    while (NULL != statement_list) {
        gencode_statement(statement_list -> statement);
        statement_list = statement_list -> statement_list;
    }
}

void gencode_statement(T_statement statement) {
    gencode_expression(statement->expression);
}

void gencode_expression(T_expression expression) {
    printf("\n");
    printf("\tmovl $%d, %%eax\n", expression->operand1->number);
    printf("\tmovl $%d, %%ebx\n", expression->operand2->number);

    switch (expression->operator->character) {
        case '+':
            printf("\taddl %%ebx, %%eax\n");
            break;
        case '-':
            printf("\tsubl %%ebx, %%eax\n");
            break;
        case '*':
            printf("\tmull %%ebx, %%eax\n");
            break;
        case '/':
            printf("\tcdq\n");
            printf("\tidiv %%ebx\n");
            break;
        default:
            assert(false);
            break;
    }
    printf("\tmovl %%eax, %%esi\n");
    printf("\tleaq .LCO(%%rip), %%rdi\n");
    printf("\tmovl $0, %%eax\n");
    printf("\tcall printf@PLT\n");
}