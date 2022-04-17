#include "../includes/parser.h"
#include "../includes/deep_copy.h"
#include "../includes/codegen.h"
#include <stdio.h>
#include <stdlib.h>

int directive_num = 1;

int main(int argc, char *argv[]) {
    /*make char array of vars*/
    /*add variables*/
    fprintf(fptr, "main:\n\t\tpush\trbp\n\t\tmov\t\trbp, rsp\n");
}

void declare_vars(FILE *fptr, char *vars[], int count) {
    for (int i = 0; i < count; i++) {
        fprintf(fptr, "%s:\n", vars[i]);
        fprintf(fptr, "\t\t.zero\t4\n");
    }
}

void 