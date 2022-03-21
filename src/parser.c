#include "parser.h"
#include "deep_copy.c"

T_token lookahead_token;

T_token get_lookahead() { //look at the next token without discarding/chaging the current token 
    return lookahead_token;
}

void next_token() {
    // // puts("next token");
    lookahead_token = get_token();
    // // puts("after lokahead");
}

/**
 * @brief 
 * 
 * @param in_loop_while  1 if in 'if', 2 if in while, 3 if in 'else', 0 if in neither
 * @return T_statement_list 
 */
T_statement_list parse_statement_list(int in_loop_while) {
    if (END != get_lookahead() -> type) { //if next token is not "END", allocate memory for the statement list and let current list equal it
        T_statement_list list = malloc(sizeof(*list));
        T_statement_list cur_list = list;
        // puts("26");
        int run = 0;
        while (1) {

            if (get_lookahead() -> type == T_WHILE)  { //if next token is a "WHILE" token
                if (get_lookahead() -> value.t_while -> type == ENDWHILE) {// if next token is an "ENDWHILE" token, get next token and break
                    next_token();
                    if (in_loop_while != 2) parser_error();
                    break;
                } else { //if next token is not an "ENDWHILE" token
                if (run++ != 0) { 
                    cur_list -> statement_list = malloc(sizeof(*cur_list)); //append memory allocated to current list
                    cur_list = cur_list -> statement_list; //update current list
                }
                    cur_list -> type = LOOP; //set current list type to loop 
                    cur_list -> statement.loop = parse_while(); //parse through the while statement
                }
            }
            else if (get_lookahead() -> type == T_IF)  {//if next token is an "IF" token

                if (get_lookahead() -> value.t_if -> type == ELSE) { //if the next token is an "ELSE" token, break
                    if (in_loop_while != 1) parser_error();
                    break;
                } else if (get_lookahead() -> value.t_if -> type == ENDIF) { //if next token is an "ENDIF" token, get next token and break
                    next_token();
                    if (in_loop_while != 1 && in_loop_while != 3) parser_error();
                    break;
                } else {
                    if (run++ != 0) {
                    cur_list -> statement_list = malloc(sizeof(*cur_list)); //append memory allocated to current list
                    cur_list = cur_list -> statement_list; //update current list
                    }
                    cur_list -> type = BRANCH; //set current list type to branch
                    cur_list -> statement.branch = parse_branch(); //parse through the branch 
                }
            } else if (get_lookahead() -> type == VAL) { //if next token is a value
                if (run++ != 0) {
                    cur_list -> statement_list = malloc(sizeof(*cur_list)); //append memory allocated to current list
                    cur_list = cur_list -> statement_list; //update current list
                }
                cur_list -> type = STATE; //set current list type to statement
                cur_list -> statement.statement = parse_statement(); //parse through the statement
            } else if (get_lookahead() -> type == END) { //if next token is "END", break
                break;
            }
        }
        return list; 
    } else {
        printf("exit inloopwhile: %d \n", in_loop_while);
        if (in_loop_while != 0) parser_error();
        return NULL;
    }
}

T_branch parse_branch() { //branch = conditional + statement_list + (if there is an "ELSE" statement, add another branch to parse through its statement_list)
    T_token if_token = get_lookahead();
    // printf("%d \n", if_token -> type);
    if (T_IF != if_token -> type || IF != if_token -> value.t_if -> type) parser_error();
    next_token();
    // puts("100");
    T_conditional conditional = parse_conditional();
    T_statement_list if_statements = parse_statement_list(1);
    T_statement_list else_statements = NULL;
    if (get_lookahead() -> type == T_IF && ELSE == get_lookahead() -> value.t_if -> type) {
        next_token();
        else_statements = parse_statement_list(3);
    }
    return create_branch(conditional, if_statements, else_statements);
}

T_branch create_branch(T_conditional conditional, T_statement_list if_statements, T_statement_list else_statements) {
    T_branch new_branch = malloc(sizeof(*new_branch));
    new_branch -> cond = conditional;
    new_branch -> if_exp = if_statements;
    new_branch -> else_exp = else_statements;
    return new_branch;
}

T_loop parse_while() { //while = conditional + statement_list 
    T_token while_token = get_lookahead();
    if (T_WHILE != while_token -> type || WHILE != while_token -> value.t_while -> type)
        parser_error();
    // puts("129");
    next_token();
    T_conditional conditional = parse_conditional();
    // puts("133");
    T_statement_list statements = parse_statement_list(2);
    // puts("135");
    return create_while(conditional, statements);
}

T_loop create_while(T_conditional conditional, T_statement_list list) {
    T_loop new_loop = malloc(sizeof(*new_loop));
    new_loop -> cond = conditional;
    new_loop -> exp = list;
    return new_loop;
}

T_conditional parse_conditional() { //conditional = lhs(left hand side) expression + comparator + rhs (right hand side) expression
    T_token token = get_lookahead();
    if (VAL != token -> type) parser_error();
    T_expression lhs = parse_expression();
    token = get_lookahead();
    if (COMP != token -> type) parser_error();
    T_comp comparator = token -> value.comp;
    next_token();
    T_expression rhs = parse_expression();
    return create_conditional(lhs, comparator, rhs);
}

T_conditional create_conditional(T_expression lhs, T_comp comparator, T_expression rhs) {
    T_conditional new_conditional = malloc(sizeof(*new_conditional));
    new_conditional -> lhs = lhs; //since lhs expression is already heap-allocated, can directly assign reference
    new_conditional -> comparator = deep_copy_comp(comparator); //deep copy comparator
    new_conditional -> rhs = rhs; //since rhs expression is already heap-allocated, can directly assign reference
    return new_conditional;
}

T_statement parse_statement() { //statement = value or variable + equal sign + rhs (right hand side) operand
    // puts("86");
    T_token token = get_lookahead();
    // printf("token type: %d \n", token -> type);
    if (VAL != token -> type || VAR != token -> value.val -> type) parser_error();
    next_token();
    // puts("90");
    T_token eq = get_lookahead();
    if (COMP != eq -> type || EQ != eq -> value.comp -> type) parser_error();
    next_token();
    // puts("94");
    T_expression rhs = parse_expression();
    // puts("95");
    return create_statement(token -> value.val, rhs);
}


T_statement create_statement(T_val lhs, T_expression rhs) {
    T_statement new_statement = malloc(sizeof(*new_statement));
    new_statement -> var = deep_copy_val (lhs); //deep copy lhs
    new_statement -> expression = rhs; //since rhs expression is already heap-allocated, can directly assign reference
    return new_statement;
}



T_expression parse_expression() { //expression = lhs (left hand side) operand + operator + rhs (right hand side) operand
    T_token lhs_token = get_lookahead(); 
    // puts("first");
    if (VAL != lhs_token -> type) parser_error();
    T_val lhs = lhs_token -> value.val;
    // if (lhs -> type == NUM)
        // printf("%f\n", *(lhs -> value.num));
    // else
        // printf("%s\n", lhs -> value.var);
    next_token();

    T_token operator_token = get_lookahead();
    // printf("%d \n", operator_token -> type);
    if (OPER != operator_token -> type) {
        return create_expression(lhs, NULL, NULL);
    }
    // puts("second");
    if (OPER != operator_token -> type) parser_error();
    T_oper operator = operator_token -> value.oper;
    next_token();
    // puts("third");
    T_expression rhs = parse_expression();

    return create_expression(lhs, operator, rhs);
}

T_expression create_expression(T_val lhs, T_oper operator, T_expression rhs) { //create expression by replacing lhs, operator, and rhs with their respective deep copy
    // puts("inside create expression");
    T_expression new_expression = malloc(sizeof(*new_expression));
    // puts("141");
    new_expression -> lhs = deep_copy_val(lhs);
    // puts("143");
    new_expression -> operator = deep_copy_oper(operator);
    // puts("145");
    new_expression -> rhs = deep_copy_expression(rhs);
    // puts("147");
    return new_expression;
}

void parser_error(){
    fprintf(stderr, "parser error\n");
    exit(1);
}
