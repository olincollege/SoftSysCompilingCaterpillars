#ifndef CODEGEN_H_
#define CODEGEN_H_

#include <assert.h>

#ifndef _STDBOOL_H
#define _STDBOOL_H

#ifndef __cplusplus

#define bool        _Bool
#define true        1
#define false        0

#else /* __cplusplus */

/* Supporting <stdbool.h> in C++ is a GCC extension.  */
#define _Bool        bool
#define bool        bool
#define false        false
#define true        true

#endif /* __cplusplus */

/* Signal that all the definitions are present.  */
#define __bool_true_false_are_defined        1

#endif        /* stdbool.h */

#include "parser.h"

void gencode_statement_list(T_statement_list statement_list);
void gencode_statement(T_statement statement);
void gencode_expression(T_expression expression);

#endif