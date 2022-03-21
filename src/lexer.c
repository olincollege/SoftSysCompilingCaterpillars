
//This lexer file reads user input one character at a time and creates tokens accordingly which are then decoded by the parser file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

//initialize variables
char identifier_str[LENGTH];
double num_val;
int op;
int last_char = ' ';

//create a token based on user input
T_token get_token() {
    // puts("inside get token");
    memset(identifier_str, 0, LENGTH);
    while (isspace(last_char) || last_char == '(' || last_char == ')') { //while the last character was a blank space or open/close bracket, read next character
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

    if (isalpha(last_char)) { //if first character is an alphabet, add it to list of characters read so far (identifier_str)
        // puts("alpha");
        int i = 0;
        identifier_str[i++] = last_char;
        while (isalnum(last_char = getchar())) { //while character is either an alphabet or a number, add it to list identifier_str and read next character
            identifier_str[i++] = last_char;
        }
        identifier_str[i] = '\0';
        if (!strcmp(identifier_str, "while") || !strcmp(identifier_str, "endwhile")) { //if "while" or "endwhile" is detected in the list identifier_str, create a while loop token
            // puts("while enter");
            return create_while_token(identifier_str);
        }
        // printf("comp: %d \n", !strcmp(identifier_str, "if"));
        if (!strcmp(identifier_str, "if") || !strcmp(identifier_str, "else") || !strcmp(identifier_str, "endif")) { //if "if" or "else" or "endif" is detected in the list identifier_str, create conditional token
            // puts("if enter");
            return create_if_token(identifier_str);
        }

        return create_var_token(identifier_str); //otherwiese create a variable token
    }

    // puts("second");

    //doesn't work with multiple periods i.e. 1.234.533
    if (isdigit(last_char) || last_char == '.') { //if first character is a number, add it to list of characters read so far (num_str) and read next character
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
        //if there is no decimal point, convert integer to floating point by adding a decimal point followed by 0s
        if (!period) {
            num_str[i] = '.'; 
        }
        num_val = strtod(num_str, 0);
        // printf("digit: %f \n", num_val);
        return create_number_token(num_val); //create number token
    }

    if (last_char == '#') { //if character is #, this is a comment - read next character and continue
        do {
            last_char = getchar();
        } while (last_char != EOF && last_char != '\n' && last_char != '\r');

        if (last_char != EOF) {
            return get_token();
        }
    }

    if (last_char == EOF) {
        return create_end_token(); //if character is an EOF, create end token
    }

    //IS THIS A REPEAT FROM LINES 16-23??? DO WE NEED THIS AGAIN???
    while (isspace(last_char) || last_char == '(' || last_char == ')') { //while the last character was a blank space or open/close bracket, read next character
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

//read single character c, and create a token accordingly
T_token create_single_char_token(char c) {
    T_token token = malloc(sizeof(*token)); //allocate memory for token
    T_oper oper = malloc(sizeof(*oper));  //allocate memory for operator
    T_comp comp = malloc(sizeof(*comp));  //allocate memory for comparator
    
    //OPER: + - / * 
    //COMP: > < = !
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

//free memory allocated to the pointer
void free_token(void *pointer) {
    free(pointer); 
}

//if character is EOF, create end token
T_token create_end_token() {
    T_token token = malloc(sizeof(T_token)); 
    token->type = END; 
    return token;
}

//if first character of user input is an alphabet and following characters are alphanumeric, create a variable token
T_token create_var_token(char* val) {
    T_token token = malloc(sizeof(*token)); 
    token->type = VAL; 
    T_val val_token = malloc(sizeof(*val_token)); 
    token->value.val = val_token;  
    token->value.val->type = VAR;
    token->value.val->value.var = malloc((strlen(val) + 1)); //allocate one extra byte for end of string character
    strcpy(token->value.val->value.var, val);

    return token;
}

//if first character of user input is a number, create a number token
T_token create_number_token(double n) {
    T_token token = malloc(sizeof(*token));
    token->type = VAL;
    T_val val_token = malloc(sizeof(*val_token));
    token->value.val = val_token;
    token->value.val->type = NUM;
    token->value.val->value.num = malloc(2); //WHY ARE WE ALLOCATING 2???
    *token->value.val->value.num = n;
    // printf("create: %f \n", *token->value.val->value.num);
    return token;
}

//if a "while" is read, create a while loop token
T_token create_while_token(char* val) {
    T_token token = malloc(sizeof(*token));
    token->type = T_WHILE;
    T_while while_token = malloc(sizeof(*while_token));
    token->value.t_while = while_token;
    token->value.t_while->type=((!strcmp(val, "while"))?WHILE:ENDWHILE);
    return token;
}

//if a "if" or "else" is read, create a conditional token
T_token create_if_token(char* val) {
    T_token token = malloc(sizeof(*token));
    token->type = T_IF;
    T_if if_token = malloc(sizeof(*if_token));
    token->value.t_if = if_token;
    token->value.t_if->type=(!strcmp(val, "if"))?WHILE:(!strcmp(val, "else")?ELSE:ENDIF);
    return token;
}

<<<<<<< HEAD
//ARE WE USING THIS?
T_token create_nl_token() {
    T_token token = malloc(sizeof(T_token));
    token->type = NL;
    return token;
}
=======
// T_token create_nl_token() {
//     T_token token = malloc(sizeof(T_token));
//     token->type = NL;
//     return token;
// }
>>>>>>> 2a74afd4efeb9e3cbad89b30c6bd18ecc2136a4f

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