# Comp-lexity Static Checker and Code Generation
Rishita Sarin, Grant Miner, Abitamim Bharmal

## Project Goal
This project, we built on our our toy compiler project from last sprint and added static checking and code generation capabilities to it. We took the parser output to generate assembly code in x86. Our lower bound was to have a functional static check and add code generation for variable declaration, arithmetic operations with two operands and one operator, and if/else statements. Time permitting, our upper bound was be to execute the same for while loops. We were able to achieve both our lower bound and upper bound goals. 

## Learning Goals

We all shared the same learning goals this project. Our primary goal was to learn and gain experience in x86 assembly language. We were also hope to develop our skills of working in a team based software project with a special focus in delegation of tasks, keeping up with documentation, and maintaing communication within the team via regular syncs.

Rishita was originally also interested in pursuing the tasks related to being a PM on a software project team. However, as it turns out there are not too many PM related tasks within this team. We all mutually delegated tasks and maintained communication. Thereby, Rishita pivoted her learning goals to gain experience in writing code from scratch in C (in addition to learning about x86). 

Grant wanted to develop a moderate ability to translate code into assembly by hand, and he was looking forward to validating the code generation for the test files.

Abitamim wanted to learn assembly and how code changes can result in assembly changes. He also wanted to learn how to structure code generation to allow for efficient traversal of the syntax tree.

## Our Work

### Stage 1 - Research
We began by looking at lectures and YouTube videos regarding the basics of what is assembly code and how to go from a parser output to produce assembly code in x86. We read through and rewrote the code generation code examples provided in toy compiler lectures and open source compilers which can be found in our resources tab. Please note that the open source compilers were written in various languages and gave us he opportunity to translate into C. Rewriting code allowed us to gain more insight on understanding the inner workings of assembly code generation and allowed us to design our assembly code syntax accordingly. 

Since we had learned about static checkers in class, we did not require additional resources regarding this topic and we focused on developing the code directly. 

### Stage 2 - Static Checker
The purpose of a static checker is to detect and report any syntactic and semantic programming errors. Our static checker begins by traversing though a list of statements to make sure no variables are used before they are declared. If they are, there will be an error and the insertion will not work. For every variable in an expression, the static checker determines if it exists in a hash map, it if does, save the value to the variable struct. If the current value is a number, add it to the value list. Then, check the remaining part of the expression. 

Similarly, the checker determines if the left hand side (LHS) and right hand side (RHS) expressions are valid in order to validate a conditional. Validating all conditionals in the if and else statements allows the static checker to validate a branch. Validating the conditionals for a while loop allows for validation of while loop functionality. 

### Stage 3 - Code Generation
The purpose of code generation is to take in the static checked parser output and covert it to assembly code (and s file) which may be used by the OS to perform the instructions provided by a program. 

Varaibles are stored in a hash table
numbers are converted to hex and then long to be constants
start with expression then build up to statement, then write conditional and statement list. from there, branch and while loop. 
and then write code to signify end of s file. 

A branch consists of a conditional and a statement list. If there is an "else" statement, it also includes another branch nested inside.

A loop consists of a conditional and the statements within.

A conditional contains a left hand side, the comparator, and a right hand side.

An expression contains two operands separated by an operator.
 
A statement contains a value or variable, an equal sign, and a right hand side.

A statement list consists of a statement, branch, or loop.
 

## Design Decision - Assembly Syntax

## Reflection

### Rishita
learned a lot - spent a lot of time researching and trying to rewrite code but got a lil bogged down by trying to translate. asking for help and coworking was very helpful. going through code and commenting and documentating have a better understanding. def want to work on scoping and asking for help earlier on. this project was better managed than the last iteration in terms of scoping and time management. excited to see the compiler go from nothing to be running and producing assembly code! Twas a great learning experience - process wise, having dedicated coworking and checkin times made the process much more smoother. debugging was fun too. 

###Grant

###Abitamim
