#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LENGTH 255


enum Token {
    tok_eof = -1,
    tok_def = -2,
    tok_identifier = -3,
    tok_number = -5,
};

char identifier_str[LENGTH];
double num_val;


int get_token() {
    memset(identifier_str, 0, LENGTH);
    int last_char = ' ';

    while (isspace(last_char)) { //if whitespace, lex next character
        last_char = getchar();
    }
    if (isalpha(last_char)) { //if last_char is alphabet, add it to identifier_str array and move to next char
        int i = 0;
        identifier_str[i++] = last_char;
        while (isalnum(last_char = getchar())) {
            identifier_str[i++] = last_char;
        }
        identifier_str[i] = '\0';
        if (strcmp(identifier_str, "def")) {
            return tok_def;
        }
        return tok_identifier;
    }

    //doesn't work with multiple periods i.e. 1.234.533
    if (isdigit(last_char) || last_char == '.') { //if last_char is a number or a ., add it to num_str array and move to next char
        char num_str[LENGTH];
        int i = 0;
        do {
            num_str[i++] = last_char;
            last_char = getchar();
        } while (isdigit(last_char) || last_char == '.');

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

    if (last_char == EOF) { //if last_char is an end of file character, return EOF token
        return tok_eof;
    }

    int ascii_val = last_char;
    return ascii_val;
}

int main(int argc, char *argv[]) {
    int r;
    while ((r = get_token()) != -1) {
        if (r == -2 || r == -3) {
            puts(identifier_str);
        } else if (r == -5) {
            printf("%f \n", num_val);
        }
    }
}   

    © 2022 GitHub, Inc.

    Terms
    Privacy
    Security
    Status
    Docs
    Contact GitHub
    Pricing
    API
    Training
    Blog
    About

