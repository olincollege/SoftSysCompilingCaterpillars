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
    memset(identifier_str, 0, LENGTH);

    T_token token = create_single_char_token(last_char);
    if (token) {
        return token;
    }
    while (isspace(last_char)) {
        if (last_char == '\n') {
            return create_nl_token();
        }
        last_char = getchar();
    }
    if (isalpha(last_char)) {
        // puts("alpha");
        int i = 0;
        identifier_str[i++] = last_char;
        while (isalnum(last_char = getchar())) {
            identifier_str[i++] = last_char;
        }
        identifier_str[i] = '\0';
        return create_val_token(identifier_str);
    }

    //doesn't work with multiple periods i.e. 1.234.533
    if (isdigit(last_char) || last_char == '.') {
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
        return create_number_token(num_val);;
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

    while (isspace(last_char)) {
        if (last_char == '\n') {
            return create_nl_token();
        }
        last_char = getchar();
    }

    T_token token = create_single_char_token(last_char);
    if (token) {
        return token;
    }
    last_char = getchar();
}

T_token create_single_char_token(char c) {
    T_token token = malloc(sizeof(T_token));
    switch (c) {
        case '+':
            token->type = OPER;
            token->value.oper->type = ADD;
            break;
        case '-':
            token->type = OPER;
            token->value.oper->type = SUB;
            break;
        case '*':
            token->type = OPER;
            token->value.oper->type = MULT;
            break;
        case '/':
            token->type = OPER;
            token->value.oper->type = DIV;
            break;
        case '>':
            token->type = OPER;
            token->value.oper->type = GT;
            break;
        case '<':
            token->type = OPER;
            token->value.oper->type = LT;
            break;
        case '=':
            token->type = OPER;
            token->value.oper->type = EQ;
            break;
        case '!': //val1 ! val2 means val1 != val2
            token->type = OPER;
            token->value.oper->type = NEQ;
        default:
            return;
    }
    return token;
}

T_token create_end_token() {
    T_token token = malloc(sizeof(T_token));
    token->type = END;
    return token;
}
T_token create_var_token(char* val) {
    T_token token = malloc(sizeof(T_token));
    token->type = VAL;
    token->value.val->type = VAR;
    token->value.val->value.var = malloc(sizeof(val));
    strcpy(val, token->value.val->value.var);

    return token;
}
T_token create_number_token(double n) {
    T_token token = malloc(sizeof(T_token));
    token->type = VAL;
    token->value.val->type = NUM;
    *token->value.val->value.var = n;

    return token;
}

T_token create_nl_token() {
    T_token token = malloc(sizeof(T_token));
    token->type = NL;
    return token;
}
// int main(int argc, char *argv[]) {
//     int r;
//     while ((r = get_token()) != -1) {
//         if (r == tok_identifier || r == tok_def) {
//             puts(identifier_str);
//         } else if (r == tok_number) {
//             printf("%f \n", num_val);
//         } else {
//             printf("%c \n", r);    
//         }
// }
// }   