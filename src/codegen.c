// https://github.com/amit9oct/Toy-Compiler/blob/master/src/codeGeneration.c
char insString[][5]={
	"add",
	"sub",
	"mov",
	"mul",
	"div",
};

char data[][20]={
	"format_in",
	"format_out_newline",
	"format_out_space",
	"global_var"
};

InstructionList* createInstruction(Instruction ins, Register operand1, Register operand2){

	InstructionList* instruction = (InstructionList*)malloc(sizeof(InstructionList));
	instruction->ins = ins;
	instruction->operand1 = operand1; 
	instruction->operand2 = operand2;
	instruction->isLabel = 0;
	return instruction;
}

InstructionList* createLabel(int labelType,int labelNum){

	InstructionList* newIns = createInstruction(-1,-1,-1,-1,-1,-1);
	newIns->isLabel = 1;
	(labelType)? sprintf(newIns->label,"T%d",labelNum):sprintf(newIns->label,"F%d",labelNum);
	return newIns;
}

Label* addLabel(int labelType,int labelNum){

	Label* newLabel = (Label*)malloc(sizeof(Label));
	newLabel->labelType = labelType;
	newLabel->labelNum = labelNum;
	return newLabel;
}

void generate(InstructionList* ins){

	if(CODE_TAIL==NULL){
		CODE_TAIL = ins;
		CODE_TAIL->next = NULL;
		CODE_HEAD = ins;
		CODE_HEAD->next = NULL;
	}
	else{
		CODE_TAIL->next = ins;
		CODE_TAIL = CODE_TAIL->next;
		CODE_TAIL->next = NULL;
	}
}


void gencode_expression(T_expression expression){
  //LHS + OPERATOR (+, -, *, /) + RHS

  //if expression is a number n, push n
  //if expression is a variable var, push var

  switch(operator):
  case "+":
    gencode_expression(LHS)
    gencode_expression(RHS)
    printf("add")

  case "-":
    gencode_expression(LHS)
    gencode_expression(RHS)
    printf("sub")

  case "*":
    gencode_expression(LHS)
    gencode_expression(RHS)
    printf("mul")

  case "/":
    gencode_expression(LHS)
    gencode_expression(RHS)
    printf("div")

  default:
    return LogErrorV("invalid operator");
}

void gencode_statement(T_statement statement){
  //VAR + EQUAL SIGN + EXPRESSION
  gencode_expression(expression)
  printf("mov")

}

void gencode_conditional(T_conditional conditional){
  //LHS + COMPARATOR (> < ! =) + RHS
  switch(operator):
  case ">":
    printf("")
  case "<":
    printf("")
  case "!":
    printf("")
  case "=":
    printf("")
  default:
    return LogErrorV("invalid comparator");
}

void gencode_statement_list(T_statement_list statement_list){
}

void gencode_branch(T_branch branch){
 //compute expression put it on stack
 //negate what we comuputed - if true go to L1 else go to L2
}

void gencode_loop(T_loop loop){
//insert L1 into code stream
//compute expression put it on stack
//negate what we computed - if true, go to L2 else continue compiling statements and then go to L1
}