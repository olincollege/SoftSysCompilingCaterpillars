#ifndef CODEGEN_H
#define CODEGEN_H

#include <assert.h> //assert()
#include <stdbool.h> //true/false

#include "parser.h"

void gencode_statement_list(T_statement_list statement_list);
void gencode_statement(T_statement statement);
void gencode_expression(T_expression expression);

#endif