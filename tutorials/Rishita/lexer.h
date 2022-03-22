#ifndf LEXER_H
#define LEXER_H

#include <stdio.h> //fgetc()
#include <ctype.h> //isdigit()
#include <sdlib.h> //exit()

typedef struct S_token* T_token;

//token is a struct where multiple types of data regarding the same item are saved in one place (similar to a class in java)
struct S_token{
    enum{ NUMBER, OPERATOR, SEMICOLON, END }
    union {
        int number;
        char character;
    };
};
T_token lex();

void lexer_error();

T_token create_end_token();
T_token create_number_token(char c);
T_token create_operator_token(char c);
T_token create_semicolon_token(); 

#endif
