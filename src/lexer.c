#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lexer.h"

char identifier_str[LENGTH];
double num_val;
int op;
int last_char = ' ';

int get_token() {
    memset(identifier_str, 0, LENGTH);

    while (isspace(last_char)) {
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
        return tok_identifier;
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
        return tok_number;
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
        return tok_eof;
    }
    // puts("ascii");
    int ascii_val = last_char;
    last_char = getchar();
    return ascii_val;
}

T_token create_end_token() {
    T_token token = malloc(sizeof(T_token));
    token.
}

int main(int argc, char *argv[]) {
    int r;
    while ((r = get_token()) != -1) {
        if (r == tok_identifier || r == tok_def) {
            puts(identifier_str);
        } else if (r == tok_number) {
            printf("%f \n", num_val);
        } else {
            printf("%c \n", r);    
        }
}
}   