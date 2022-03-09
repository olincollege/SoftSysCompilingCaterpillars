#define LENGTH 255

typedef struct S_token* T_token;
typedef struct S_oper* T_oper;
typedef struct S_comp* T_comp;

struct S_token {

    enum {NUMBER, VAR, END} ;

    double num;
    char var[LENGTH];
};

struct S_oper {
    enum{
        ADD, SUB, MULT, DIV
    };
};

struct S_comp {
    enum {
        EQ, LT, GT
    };
};