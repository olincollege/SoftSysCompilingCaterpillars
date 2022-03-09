#ifndf LEXER_H
#define LEXER_H

#define LENGTH 255

typedef struct S_token* T_token;
typedef struct S_val* T_val;
typedef struct S_oper* T_oper;
typedef struct S_comp* T_comp;

struct S_token {
    enum {VAL, OPER, COMP, NL, END} type;//NL is new line, END is end
    union {
        T_val val;
        T_oper oper;
        T_comp comp;
    } value;
};

struct S_val {
    enum {NUMBER, VAR} type;
    union {
        double *num;
        char (*var)[LENGTH];
    } value;
};

struct S_oper {
    enum{
        ADD, SUB, MULT, DIV
    } type;
};

struct S_comp {
    enum {
        EQ, LT, GT
    } type;
};

T_token create_end_token();
T_token create_var_token(char* val);
T_token create_number_token(double n);
T_token create_operator_token(char c);
T_token create_comp_token(char c);
T_token create_nl_token();

#endif