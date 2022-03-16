#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lexer.h"

char identifier_str[LENGTH];
double num_val;
int op;
int last_char = ' ';

T_token get_token() {
    // puts("inside get token");
    memset(identifier_str, 0, LENGTH);
    while (isspace(last_char) || last_char == '(' || last_char == ')') {
        // puts("space");
        // if (last_char == '\n') {
        //     last_char = getchar();
        //     return create_nl_token();
        // }
        // puts("getchar");
        last_char = getchar();
    }
    // puts("first");
    // printf("%c \n", last_char);
    // T_token token = create_single_char_token(last_char);
    // if (token) {
    //     last_char = getchar();
    //     return token;
    // }

    if (isalpha(last_char)) {
        // puts("alpha");
        int i = 0;
        identifier_str[i++] = last_char;
        while (isalnum(last_char = getchar())) {
            identifier_str[i++] = last_char;
        }
        identifier_str[i] = '\0';
        if (!strcmp(identifier_str, "while") || !strcmp(identifier_str, "endwhile")) {
            // puts("while enter");
            return create_while_token(identifier_str);
        }
        // printf("comp: %d \n", !strcmp(identifier_str, "if"));
        if (!strcmp(identifier_str, "if") || !strcmp(identifier_str, "else") || !strcmp(identifier_str, "endif")) {
            // puts("if enter");
            return create_if_token(identifier_str);
        }

        return create_var_token(identifier_str);
    }

    // puts("second");

    //doesn't work with multiple periods i.e. 1.234.533
    if (isdigit(last_char) || last_char == '.') {
        // puts("beta");
        char num_str[LENGTH];
        memset(num_str, 0, LENGTH);
        int i = 0;
        int period = 0;
        do {
            num_str[i++] = last_char;
            last_char = getchar();
            if (last_char == '.') {
                period = 1;
            }
        } while (isdigit(last_char) || last_char == '.');
        if (!period) {
            num_str[i] = '.';
        }
        num_val = strtod(num_str, 0);
        // printf("digit: %f \n", num_val);
        return create_number_token(num_val);
    }

    if (last_char == '#') {
        do {
            last_char = getchar();
        } while (last_char != EOF && last_char != '\n' && last_char != '\r');

        if (last_char != EOF) {
            return get_token();
        }
    }

    if (last_char == EOF) {
        return create_end_token();
    }

    while (isspace(last_char) || last_char == '(' || last_char == ')') {
        // puts("camma");
        // if (last_char == '\n') {
        //     last_char = getchar();
        //     return create_nl_token();
        // }
        last_char = getchar();
    }

    T_token token = create_single_char_token(last_char);
    last_char = getchar();
    if (token != NULL) {
        return token;
    }
}

T_token create_single_char_token(char c) {
    T_token token = malloc(sizeof(*token));
    T_oper oper = malloc(sizeof(*oper));
    T_comp comp = malloc(sizeof(*comp));

    switch (c) {
        case '+':
            token->type = OPER;
            oper->type = ADD;
            token->value.oper = oper;
            free_token(comp);
            break;
        case '-':
            token->type = OPER;
            oper->type = SUB;
            token->value.oper = oper;
            free_token(comp);
            break;
        case '*':
            token->type = OPER;
            oper->type = MULT;
            token->value.oper = oper;
            free_token(comp);
            break;
        case '/':
            token->type = OPER;
            oper->type = DIV;
            token->value.oper = oper;
            free_token(comp);
            break;
        case '>':
            token->type = COMP;
            comp->type = GT;
            token->value.comp = comp;
            free_token(oper);
            break;
        case '<':
            token->type = COMP;
            comp->type = LT;
            token->value.comp = comp;
            free_token(oper);
            break;
        case '=':
            token->type = COMP;
            comp->type = EQ;
            token->value.comp = comp;
            free_token(oper);
            break;
        case '!': //val1 ! val2 means val1 != val2
            token->type = COMP;
            comp->type = NEQ;
            token->value.comp = comp;
            free_token(oper);
            break;
        default:
            free_token(oper);
            free_token(comp);
            return NULL;
    }
    return token;
}

void free_token(void *pointer) {
    free(pointer);
}

T_token create_end_token() {
    T_token token = malloc(sizeof(T_token));
    token->type = END;
    return token;
}
T_token create_var_token(char* val) {
    T_token token = malloc(sizeof(*token));
    token->type = VAL;
    T_val val_token = malloc(sizeof(*val_token));
    token->value.val = val_token;
    token->value.val->type = VAR;
    token->value.val->value.var = malloc((strlen(val) + 1));
    strcpy(token->value.val->value.var, val);

    return token;
}
T_token create_number_token(double n) {
    T_token token = malloc(sizeof(*token));
    token->type = VAL;
    T_val val_token = malloc(sizeof(*val_token));
    token->value.val = val_token;
    token->value.val->type = NUM;
    token->value.val->value.num = malloc(2);
    *token->value.val->value.num = n;
    // printf("create: %f \n", *token->value.val->value.num);
    return token;
}

T_token create_while_token(char* val) {
    T_token token = malloc(sizeof(*token));
    token->type = T_WHILE;
    T_while while_token = malloc(sizeof(*while_token));
    token->value.t_while = while_token;
    token->value.t_while->type=((!strcmp(val, "while"))?WHILE:ENDWHILE);
    return token;
}

T_token create_if_token(char* val) {
    T_token token = malloc(sizeof(*token));
    token->type = T_IF;
    T_if if_token = malloc(sizeof(*if_token));
    token->value.t_if = if_token;
    token->value.t_if->type=(!strcmp(val, "if"))?WHILE:(!strcmp(val, "else")?ELSE:ENDIF);
    return token;
}

T_token create_nl_token() {
    T_token token = malloc(sizeof(T_token));
    token->type = NL;
    return token;
}

// int main(int argc, char *argv[]) {
//     T_token r;
//     while ((r = get_token())->type != END) {
//         if (r->type == VAL) {
//             if (r->value.val->type == NUM) {
//                 printf("type: %d type: %d  value: %f \n", r->type, r->value.val->type, *r->value.val->value.num);
//             } else {
//                 printf("type: %d type: %d value: %s \n", r->type, r->value.val->type, r->value.val->value.var); 
//             }
//         } else if (r->type == NL) {
//             puts("NL");
//         } else if (r->type == COMP) {
//             printf("type: %d  value: %d \n", r->type, r->value.comp->type);
//         } else if (r->type == OPER) {
//             printf("type: %d  value: %d \n", r->type, r->value.oper->type);
//         } else if (r->type == T_IF) {
//             printf("if type: %d \n", r->value.t_if->type);
//         } else if (r->type == T_WHILE) {
//             printf("while type: %d \n", r->value.t_while->type);
//         }
// }
// }   