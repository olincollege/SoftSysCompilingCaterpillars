#include "../includes/parser.h"
#include "../includes/deep_copy.h"

T_token lookahead_token;

/* Looks at the next token without discarding the current one
*
*  returns the next token
*/
T_token get_lookahead() {
    return lookahead_token;
}

// retrieves the next token
void next_token() {
    lookahead_token = get_token();
}

/**
 * @brief Creates a T_statement_list
 * 
 * @param in_loop_while int where 1 if in 'if', 2 if in while, 3 if in 'else', 0 if in neither
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

/**
 * @brief A branch consists of a conditional and a statement list. If there is
 * an "else" statement, it also includes another branch nested inside.
 * 
 * This function parses a branch
 * 
 * @return T_branch containing the conditional, if body, and else body
 */
T_branch parse_branch() {
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

/**
 * @brief Create a branch object
 * 
 * @param conditional T_conditional that determines whether if branch runs
 * @param if_statements T_statement_list for the "if" section of the branch
 * @param else_statements T_statement_list for the "else" section of the branch
 * @return T_branch 
 */
T_branch create_branch(T_conditional conditional, T_statement_list if_statements, T_statement_list else_statements) {
    T_branch new_branch = malloc(sizeof(*new_branch));
    new_branch -> cond = conditional;
    new_branch -> if_exp = if_statements;
    new_branch -> else_exp = else_statements;
    return new_branch;
}

/**
 * @brief A T_loop consists of a conditional and the statements within
 * 
 * This function parses those sections and creates a T_loop
 * 
 * @return T_loop 
 */
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

/**
 * @brief Create a loop object
 * 
 * @param conditional T_conditional that determines whether the loop runs again
 * @param list statement list containing the expressions between "while" and
 *             "endwhile"
 * 
 * @return T_loop 
 */
T_loop create_while(T_conditional conditional, T_statement_list list) {
    T_loop new_loop = malloc(sizeof(*new_loop));
    new_loop -> cond = conditional;
    new_loop -> exp = list;
    return new_loop;
}

/**
 * @brief parses conditional statement
 * Conditional contains a left hand side, the comparator, and a right hand side
 * 
 * @return T_conditional 
 */
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

/**
 * @brief Create a conditional token
 * 
 * @param lhs expression on the left side of the comparator
 * @param comparator comparator
 * @param rhs expression on the right side of the comparator
 * @return T_conditional 
 */
T_conditional create_conditional(T_expression lhs, T_comp comparator, T_expression rhs) {
    T_conditional new_conditional = malloc(sizeof(*new_conditional));
    new_conditional -> lhs = lhs; //since lhs expression is already heap-allocated, can directly assign reference
    new_conditional -> comparator = deep_copy_comp(comparator); //deep copy comparator
    new_conditional -> rhs = rhs; //since rhs expression is already heap-allocated, can directly assign reference
    return new_conditional;
}

/**
 * @brief Parses a statement
 * A statement contains a value or variable, an equal sign, and a right hand side
 * 
 * @return T_statement 
 */
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

/**
 * @brief Create a statement token
 * 
 * @param lhs left half of statement
 * @param rhs right half of statement
 * @return T_statement 
 */
T_statement create_statement(T_val lhs, T_expression rhs) {
    T_statement new_statement = malloc(sizeof(*new_statement));
    new_statement -> var = deep_copy_val (lhs); //deep copy lhs
    new_statement -> expression = rhs; //since rhs expression is already heap-allocated, can directly assign reference
    return new_statement;
}

/**
 * @brief Parses an expression
 * Expression contains two operands separated by an operator
 * 
 * @return T_expression 
 */
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

/**
 * @brief Create an expression token
 * 
 * @param lhs left side of expression
 * @param rhs right side of expression
 * @return T_expression 
 */
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

/**
 * @brief Raises error if parser fails
 * 
 */
void parser_error(){
    fprintf(stderr, "parser error\n");
    exit(1);
}
