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

  generate(createInstruction(MOVSS, XMM0, XMM1));

  switch(operator):
  case "+":{
		generate(createInstruction(ADDSS, XMM0, XMM1));
	}
	break;

		case "-":{
		generate(createInstruction(SUBSS, XMM0, XMM1));
	}
	break;

  case "*":{
		generate(createInstruction(MULSS, XMM0, XMM1));
  }
  break;

  case "/":{
		generate(createInstruction(DIVSS, XMM0, XMM1));
  }
  break;

  default:
    return LogErrorV("invalid operator");
}

  generate(createInstruction(MOVSS, XMM1, XMM0));



void gencode_statement(T_statement statement){
  //VAR + EQUAL SIGN + EXPRESSION
  gencode_expression(expression)
  printf("movss")

}
