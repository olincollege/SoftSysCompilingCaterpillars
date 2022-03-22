#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LENGTH 255


enum tokenType {
    tok_eof = -1,
    tok_def = -2,
    tok_identifier = -3,
    tok_number = -5,
    tok_operator = -6,
    tok_if = -7,
    tok_then = -8,
    tok_else = -9
};

char identifier_str[LENGTH];
double num_val;
int op;

int get_token() {
    memset(identifier_str, 0, LENGTH);
    int last_char = ' ';

    while (isspace(last_char)) {
        last_char = getchar();
    }
    if (isalpha(last_char)) {
        int i = 0;
        identifier_str[i++] = last_char;
        while (isalnum(last_char = getchar())) {
            identifier_str[i++] = last_char;
        }
        identifier_str[i++] = '\0';
        if (!strcmp(identifier_str, "def")) {
            return tok_def;
        }
        if (!strcmp(identifier_str, "if")) return tok_if;
        if (!strcmp(identifier_str, "then")) return tok_then;
        if (!strcmp(identifier_str, "else")) return tok_else;
        return tok_identifier;
    }

    //doesn't work with multiple periods i.e. 1.234.533
    if (isdigit(last_char) || last_char == '.') {
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

    if (last_char == EOF) {
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
        } else {
            printf("%d \n", r);
        }
    }
}   

// #include <stdlib.h>
// #include <stdio.h>
// #include <ctype.h>
// #include <string.h>

// enum token {
//     tok_eof = -1,
    
//     tok_def = -2,
//     tok_extern = -3,
    
//     tok_identifier = -4,
//     tok_number = -5,

//     tok_if = -6,
//     tok_then = -7,
//     tok_else = -8
// };

// static char *identifier_str;
// static double numVal;

// static int get_tok() {
//     static char lastChar = ' ';

//     while (isspace(lastChar)) {
//         lastChar = getchar();
//     }

//     if (isalpha(lastChar)) {
//         strcpy(identifier_str, &lastChar);
//         char *identifier_str_up = identifier_str +1;

//         while (isalnum(lastChar = getchar())) {
//             strcat(identifier_str_up, & lastChar);
//             identifier_str_up ++;
//         }

//         if (!strcmp(identifier_str, "def")) return tok_def;
//         if (!strcmp(identifier_str, "extern")) return tok_extern;
//         if (!strcmp(identifier_str, "if")) return tok_if;
//         if (!strcmp(identifier_str, "then")) return tok_else;
//         if (!strcmp(identifier_str, "else")) return tok_else;
//         return tok_identifier;
//     }

//     if (isdigit(lastChar) || lastChar == '.') {
//         char *numStr;
//         do {
//             numStr += lastChar;
//             lastChar = getchar();
//         } while (isdigit(lastChar || lastChar == '.'));

//         numVal = strtod(numStr, NULL);
//         return tok_number;
//     }

//     if (lastChar == '#') {
//         do {
//             lastChar = getchar();
//         } while (lastChar != -1 && lastChar != '\n' && lastChar != '\r');

//         if (lastChar != -1) {
//             return get_tok();
//         }
//     }

//     if (lastChar == -1) {
//         return tok_eof;
//     }

//     int thisChar = lastChar;
//     lastChar = getchar();
//     return thisChar;
// }

// // struct ExprAST {
    
// // };

// // struct NumberExprAst {
// //     double Val;
// // };

// // void NumberExprAst (double Val) {

// // }

// int main() {

//     return 0;
// }