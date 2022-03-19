#ifndef LEXER_H
#define LEXER_H

#define LENGTH 255

//save tokens as structs so that we can save all the information regarding each token (various data types) in one place
typedef struct S_token* T_token;
typedef struct S_val* T_val;
typedef struct S_oper* T_oper;
typedef struct S_comp* T_comp;
typedef struct S_while* T_while;
typedef struct S_if* T_if;


struct S_token { 
    // enum identifies what type of token it is
    enum {VAL, OPER, COMP, NL, END, T_WHILE, T_IF} type;//NL is new line, END is end
    union {
        T_val val;
        T_oper oper;
        T_comp comp;
        T_while t_while;
        T_if t_if;
    } value;
};

struct S_val { //number and variable 
    enum {NUM, VAR} type;
    union {
        double *num;
        char *var;
    } value;
};

struct S_oper { //operators: + - * /
    enum{
        ADD, SUB, MULT, DIV
    } type;
};

struct S_comp { //comparison operators: = > < !
    enum {
        EQ, LT, GT, NEQ
    } type;
};

struct S_while { //while and endwhile
    enum {
        WHILE, ENDWHILE
    } type;
};

struct S_if { //if, else, and endif
    enum {
        IF, ELSE, ENDIF
    } type;
};

void free_token(void *pointer); 
T_token create_end_token();
T_token create_var_token(char* val);
T_token create_while_token(char* val);
T_token create_if_token(char* val);
T_token create_number_token(double n);
T_token create_nl_token();
T_token create_single_char_token(char c);
T_token get_token();

#endif