#include "lexer.h"

//allocate space the size of token, set token kind to equal "END", return the token
T_token create_end_token() { 
    T_token token = malloc(sizeof(*token));
    token->kind = END;
    return token;
}

//allocate space the size of token, set token kind to equal "NUMBER", set token number to c, return the token
T_token create_number_token(char c) { 
    T_token token = malloc(sizeof(*token));
    token->kind = NUMBER;
    token->number = c - '0';
    return token;
}


//allocate space the size of token, set token kind to equal "OPERATOR", set token character to c, return the token
T_token create_operator_token(char c) { 
    T_token token = malloc(sizeof(*token));
    token->kind = OPERATOR;
    token->character = c;
    return token;
}


//allocate space the size of token, set token kind to equal "SEMICOLON", return the token
T_token create_semicolon_token(char c) { 
    T_token token = malloc(sizeof(*token));
    token->kind = SEMICOLON;
    return token;
}

T_token lex() {
    char c = fgetc(stdin); 
    if (EOF ==c) {
        return create_end_token(); //if c is an end of file, create an end token
    } else if (isdigit(c) {
        return create_number_token(c); //if c is a number, create a number token
    } else if (isspace(c)) { //if c is a space, continue lexing without adding any new tokens
        // skip whitespace and get the next token
        return lex();
    } else if (';' == c) { //if c is ; create a semicolon token
        return create_semicolon_token();
    } else { //if c is any of the four operators (*, +, -, /), create an operator token
        //covers the remaining cases
        switch (c) { 
            case '+':
            // fall through
            case '-':
            // fall through
            case '*':
            // fall through
            case '/':
                return create_operator_token(c);
            default:
            // covers the remaining cases 
            lexer_error();
            break;
        }
    }
}

//if c is anything other than a number, EOF, operators, or a semicolon, throw lexing error
void lexer_error() {
    fprintf(stderr, "lexer error\n");
    exit(1);
}
