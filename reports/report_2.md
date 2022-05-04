# Comp-lexity Static Checker and Code Generation
Rishita Sarin, Grant Miner, Abitamim Bharmal

## Project Goal
The goal of this project was to develop static checking and assembly code generation capabilities in our compiler. A compiler takes source code written in high level languages such as python and C and converts it into machine code which can be interpreted by the CPU of the computer. Compilers have a front-end and back-end interface.

Our basic toy compiler performs arithmetic functions namely addition, subtraction, multiplication, and division on floating numbers (one operation at a time - example 1 + 2 would yield 3) and assign numerical values to variables (example a = 4). It also has if/else statement and while loop interpretation functionality to perform advanced operations.

This project, we took the parser output to generate assembly code in x86. Our lower bound was to have a functional static check and add code generation for variable declaration, arithmetic operations with two operands and one operator, and if/else statements. Time permitting, our upper bound was be to execute the same for while loops. We were able to achieve both our lower bound and upper bound goals. 

## Learning Goals

We all shared the same learning goals this project. Our primary goal was to learn and gain experience in x86 assembly language. We were also hope to develop our skills of working in a team based software project with a special focus in delegation of tasks, keeping up with documentation, and maintaing communication within the team via regular syncs.

Rishita was originally also interested in pursuing the tasks related to being a PM on a software project team. However, as it turns out there are not too many PM related tasks within this team. We all mutually delegated tasks and maintained communication. Thereby, Rishita pivoted her learning goals to gain experience in writing code from scratch in C (in addition to learning about x86).

Grant wanted to develop a moderate ability to translate code into assembly by hand, and he was looking forward to validating the code generation for the test files. x86 is much more complex than the language he was more familiar with, RISC-V, so there were many commands and syntax forms that were unfamiliar.

Abitamim wanted to learn assembly and how code changes can result in assembly changes. He also wanted to learn how to structure code generation to allow for efficient traversal of the syntax tree.

## Our Work

### Stage 1 - Research
We began by looking at lectures and YouTube videos regarding the basics of what is assembly code and how to go from a parser output to produce assembly code in x86. We read through and rewrote the code generation code examples provided in toy compiler lectures and open source compilers which can be found in our [resources tab](https://github.com/olincollege/SoftSysCompilingCaterpillars/blob/main/resources/links.md). Please note that the open source compilers were written in various languages and gave us he opportunity to translate into C. Rewriting code allowed us to gain more insight on understanding the inner workings of assembly code generation and allowed us to design our assembly code syntax accordingly. 

Since we had learned about static checkers in class, we did not require additional resources regarding this topic and we focused on developing the code directly. 

The majority of the guidance for the general syntax was informed by code translations performed using [GodBolt.org](https://www.godbolt.org). Many test scripts were entered into the tool in C syntax. We analyzed the output of this tool to develop the general structures of different code structures such as if/else branches and while loops. We also used the tool to gain an understanding of how to declare our variables and constants and also how to begin and end the assembly file. We also relied on a [guide](https://www.cs.virginia.edu/~evans/cs216/guides/x86.html) from the University of Virginia to understand the available registers and basic commands.

### Stage 2 - Static Checker
The purpose of a static checker is to detect and report any syntactic and semantic programming errors. Our static checker begins by traversing though the tree to make sure no variables are used before they are declared. If they are, there will be an error thrown. For every variable in an expression, the static checker determines if it exists in a hash map, it if does, it continues. If the expression is part of a statement, after checking the expression, the variable the expression is being assigned to is added to the hash map. If it is already present there, it does nothing. Every number in an expression is added to the value list.

The checker determines if the left hand side (LHS) and right hand side (RHS) expressions are valid in a conditional. Validating all conditionals in the if and else statements allows the static checker to validate a branch. Validating the conditionals for a while loop allows for validation of while loop functionality. 

### Stage 3 - Code Generation
The purpose of code generation is to take in the static checked parser output and covert it to assembly code (a .s file) which may be used by the OS to perform the instructions provided by a program. We began developing the assembly code generation code by starting from the least to most complex unit that needed to be presented in the assembly code .s file. 

### Stage 3.1 - Defining Variables

We begin by extracting the variables from the source file. The static checker outputs a struct that contains a GHashTable and a GArray, both data structures from Glib. The GHashTable in particular holds the names of the variables. We use the g_hash_table_foreach() function to iterate through the hashtable and write the variables into the output file.

```
var1:
    .zero 4
```
`var1` represents the variable name, and `.zero` clears `4` bytes of memory after to hold the value of `var1`.

### Stage 3.2 - Defining Constants
Next, any numbers are converted from a float to hex and hex to a long int to be presented as a constant in the assembly code. We are not completely clear if all of these conversions need to take place, but we have decided to err on the side of the example output from [GodBolt](https://godbolt.org). 

```c
void declare_constants(FILE* fptr, GArray* nums) {
    int i = 0;
    float num;
    for (; i < nums -> len; i++) {
        num = g_array_index(nums, float, i);
        //convert float to hex, then hex to int
        char hex[20];
        snprintf(hex, sizeof(hex), "0x%x", *(unsigned int*)&num);
        //print constant declaration
        fprintf(fptr, ".LC%d:\n", i);
        //print constant value
        fprintf(fptr, "\t.long\t%d\n", (int)strtol(hex, NULL, 0));
    }
}
```

### Stage 3.3 - Expressions
Once we had the variables and numbers stored, we expanded to coding for an expression which contains any two operands seperated by an operator. 

The first step in this process is to make the left hand side of the expression, or whatever comes before the operator. We chose to iterate left to right and ignore the order of operations and parentheses to simplify our code generation.

The `T_expression` contains a `T_val` which can either hold a variable or a number. The switch statement below moves that value into one of the `xmm` registers and accounts for type.

```c
void generate_expression(FILE *fptr, T_expression side, int reg) {
    switch (side->lhs->type) { //left side of expression (num or var)
        case NUM: 
            fprintf(fptr, "\tmovss\txmm%d, .LC%d[rip]\n", reg, curr_const++);
            break;
        case VAR:
            fprintf(fptr, "\tmovss\txmm%d, %s[rip]\n", reg, side->lhs->value.var);
    }
```

The same step is then repeated for the right half of the expression, where the value is moved into a different `xmm` register.

The final portion of an expression is the operation executed on the operand.

```c
switch(side->operator->type) {
    case ADD:
        fprintf(fptr, "\taddss\t");
        break;
    case SUB:
        fprintf(fptr, "\tsubss\t");
        break;
    case MULT:
        fprintf(fptr, "\tmulss\t");
        break;
    case DIV:
        fprintf(fptr, "\tdivss\t");
}
fprintf(fptr, "xmm%d, xmm%d\n", reg, reg+1);
```

### Stage 3.4 - Statements
The next steps involved presenting a statement in x86 which contains a variable, an equal sign, and a right hand side expression.

```c
fprintf(fptr, "\tmovss\t%s[rip], xmm0\n", statement->var->value.var);
```
This line simply moves the result of the right hand expression (always put into `xmm0`) into the variable.

### Stage 3.5 - Statement Lists/Iterator
We defined statement lists as structs that contained a pointer to a statement and a pointer to another statement list. This linked list style of architecture allowed us to avoid memory overuse while still capturing all the statements. 

Generally, the statement list generator determined which type of statement it held, either a statement, a branch, or a loop. It then called the appropriate function to deal with each of those.

The generator runs through the list until the statement list is NULL (it has reached the final statement).

```c
while (sl != NULL && sl->statement_list!=NULL) {
    ...
    sl = sl->statement_list;
}
```
Statement generation happens where the `...` are.

### Stage 3.6 - Advanced Structures
From here, we coded are most complex units which were branches and while loops. Branches contain a conditional and two statement lists (one for if, and one for else). Loops contain a conditional and one statement list.

Both of these structures require conditional statements, which were made using the expression generation function on each side of the function, saving the results into registers `xmm0` and `xmm1`. These two registers were then compared using the `comiss` operation. `comiss` sets several flags based on the result of the comparison.

```c
void generate_conditional(FILE *fptr, T_conditional cond) {
    generate_expression(fptr, cond->lhs, 0); //left side
    generate_expression(fptr, cond->rhs, 1); //right side
    fprintf(fptr, "\tcomiss\t%%xmm1, %%xmm0\n"); //compare the two
}
```

Because the jump behavior is dependent on whether the conditional is in an if/else statement or a while loop, the jumping behavior after the comparison is handled in those sections.

```c
switch (branch->cond->comparator->type) {    
    case EQ:
        fprintf(fptr, "\tjne\t"); //jump if not equal
        break;
    case LT:
        fprintf(fptr, "\tjge\t"); //jump if greater or equal
        break;
    case GT:
        fprintf(fptr, "\tjle\t"); //jump if less or equal
        break;
    case NEQ:
        fprintf(fptr, "\tjeq\t"); //jump if equal
}
```

The jump commands appear to be the opposites of the comparator types because assembly code is written so that the jump happens if a condition is met, rather than if it is not as in C code.

Our generate_branch() function saves a location number for the else statement and the end of the else statement. After executing the conditional, the program counter either jumps to the else statement or continues running. If the main branch is taken, it must then jump past the else statement in the code. 

The generate_loop() function only saves the location number of the beginning of the loop and the line just past the end of the loop. If the condition is not met, it jumps out of the loop. If the code in the loop runs, the program jumps back to the beginning of the loop to check the condition again. 

### Stage 3.7 - The End
Finally, to signify the end of assembly code in a s file, we insert some final code that restores the stack to what it was before the file ran, updates the program counter, and clears the argument register.


## Design Decision - Assembly Syntax

There were many design decisions to be made regarding the syntax we would use for our x86 code generator. Among the most significant was the choice to use Intel syntax instead of AT&T syntax. While we have translated our generator to have a parallel generator for AT&T, Intel syntax is the way the output from [GodBolt](https://godbolt.org) was originally formatted. We also decided to use floats for all of our constants, which is why most of our instructions end with "ss," to denote that they are instructions designed for single precision floats. 

Another key decision we made was in the way we crafted our if/else statements and while loops. While it may have been a necessary move, we made the explicit decision to created named memory locations and store their values as local variables based on a global iterator. This did result in some named location that were immediately preceded by another, but it made the generation much simpler.

## Reflection

### Rishita

This project was a major learning experience for me. Some of my teammates came to this project with more advanced skills in this area of assembly code than I did. Thereby I spent the first bit of the project speed learning and catching up with them. This required researching the topic of assembly code by reading and taking notes on lectures and YouTube videos found online. I also met up with Grant to ensure that my understanding of the material was accurate. The next part of my work in this project involved gathering and rewriting pre-existing code generation code. This was somewhat of a treacherous journey to say the least. Much of the code I found was not written in C so I focused on translating it to C while also ammending the code such that it was compatible with our assembly code syntax. I unfortunately got stuck in the weeds during this process. During this time, coworking with my teammates was helpful because they would kidnly redirect me if I was getting stuck in the translation process. I enventually realized that it was not worth trasnalting and adding compatibility of existing code. Thus, I worked with my teammates to write our assembly code generation code from scratch in C. During this process, I also went through an commmented the code written by my teammates to ensure a deeper understanding of the material. Finally, I also had the opportunity to debug code. It was fun challenge where we took a methodical approach to pin point our issues. It was so rewarding to watch our bugs finally get resolved. 

Process wise, this project was better managed and scoped than our pervious iteration as a team. We were consistantly on the same page as a team with the current progress and future goals of the project and had more overlapping work time to help each other. Our regular checkins and co-working sessions made a real difference in the team health and the overall quality of the project. I am excited and proud to see our compiler go from nothing to running and producing assembly code. Overall, I was able to acheive my learning goals as well as learn new teaming and technical skills along the way. 

### Grant

I came into this project with a basic understanding of how assembly instructions and different registers are structured, but I did not know anything about x86. When doing the code generation by hand, I found myself spotting important design decisions we needed to make. After several whiteboards and many sheets of printer paper were filled with assembly, I already felt proud. When we moved into the implementation of the code generation, I was excited. I wish I had spent more time thinking about the implemenation. I'm not sure that fprintf() was the best implementation method for writing our commands into an output file, and I felt like some of the moves I made were done without much consideration for future steps, unlike the architectural decisions we made in the first phase of this project. Despite all this, as each new function proved to be running, I was given dopamine hit after dopamine hit, culminating in a moment of triumph when the generator spat out the expected code for the file it was fed. I am very proud of the work I have done on this project, but there is definitely more room to extend this. I look forward to augmenting this basic compiler in the near future.

### Abitamim

 I came into the project knowing nothing about assembly. I learned a lot about how various operations, such as loops, branches, and arithmetics, are created in assembly. I also became far more proficient at using more advanced data structures by implementing the static checker with glib, along with the code generation for the constants and variables. I initally wanted to build an iterator for the tree, which would have helped me learn how to best structure code generation. However, this ended up being more complicated than expected, since there could be an unknown number of layers, which would have required building a stack, rather than using recursion and exploiting the stack provided by the OS. When the program finally generated assembly code, however, all the work we have done over the semester was validated and I was elated! I am happy with how this project has gone, and hope to learn how to build more sophisticated compilers in the future.
