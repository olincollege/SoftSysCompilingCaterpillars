#include "lexer.h"
#include "parser.h"
#include "code_gen.h"

int main (int argc, char **argv) {
    next_token();

    T_statement_list statement_list = parse_statement_list();

    gencode_statement_list(statement_list);

    return 0;
}