#include "parser.h"

T_expression test_parse_expression() {
    // printf("x + 5 - 3");
    T_expression exp = parse_expression();
    return exp;
}

int main() {
    // puts("inside");
    next_token();
    // printf("%d \n", get_lookahead() -> type);
    T_expression exp = test_parse_expression();
    while (exp -> operator != NULL) {
        printf("%f %d \n", *(exp -> lhs -> value.num), (exp -> operator -> type));
        exp = exp -> rhs;
    }
    printf("%f \n", *(exp -> lhs -> value.num));
}