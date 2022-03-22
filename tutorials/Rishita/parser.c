#include "parser.h"

T_token lookahead_token;

T_token get_lookahead() { //look at next token
    return lookahead_token;
}

void next_token() {
    lookahead_token = lex();
}

T_statement_list parse_statement_list() {
    if (END != get_lookahead() ->kind) { //if the next token is not the end of the file, parse through the next statement else return null
        T_statement statement = parse_statement(); 
        T_statement_list statement_list = parse_statement_list();
        return create_statement_list(statement, statement_list);
    }   else {
        return NULL;
    }
}

T_expression parse_expression() {
    T_token operand1 = get_lookahead(); //if the first token is not a number, throw an error
    if (NUMBER != operand1->kind) parse_error();
    next_token();

    T_token operator = get_lookahead(); //if the next token is not an operator, throw an error
    if (OPERATOR != operator->kind) parse_error();
    next_token();

    T_token operand2 = get_lookahead(); //if the next token is not a number, throw an error
    if (NUMBER != operand2->kind) parse_error();
    next_token();

    return create_expression(operand1, operator, operand2);
}

T_statement_list create_statement_list(T_statement statement, T_statement_list statement_list) {
    T_statement_list new_list = malloc(sizeof(*new_list)); //allocate memory as you add a new statement
    new_list->statement = statement;
    new_list->statement_list = statement_list;
    return new_list;
}

T_statement create_statement(T_expression expression) {
    T_statement new_statement = malloc(sizeof(*new_statement));
    new_statement->expression = expression; //a new statement is made up of an expression
    return new_statement;
}

T_expresion create_expression(T_token operand1, T_token operator, T_token operand2) { //expression = operand1 + operator + operand2
    T_expression new_expresion = malloc(sizeof(*new_expresion));
    new_expresion->operand1 = operand1;
    new_expresion->operator = operator;
    new_expresion->operand2 = operand2;
    return new_expresion;
}

void parser_error() {
    fprintf(stderr, "parser error\n");
    exit(1);
}
