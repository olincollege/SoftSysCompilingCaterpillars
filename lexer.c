#include "lexer.h"

T_token create_end_token() { 
    T_token token = malloc(sizeof(*token));
    token->kind = END;
    return token;
}

T_token create_number_token(char c) { 
    T_token token = malloc(sizeof(*token));
    token->kind = NUMBER;
    token->number = c - '0';
    return token;
}

T_token create_operator_token(char c) { 
    T_token token = malloc(sizeof(*token));
    token->kind = OPERATOR;
    token->character = c;
    return token;
}

T_token create_semicolon_token(char c) { 
    T_token token = malloc(sizeof(*token));
    token->kind = SEMICOLON;
    return token;
}

T_token lex() {
    char c = fgetc(stdin);
    if (EOF ==c) {
        return create_end_token();
    } else if (isdigit(c) {
        return create_number_token(c);
    } else if (isspace(c)) {
        // skip whitespace and get the next token
        return lex();
    } else if (';' == c) {
        return create_semicolon_token();
    } else {
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

void lexer_error() {
    fprintf(stderr, "lexer error\n");
    exit(1);
}