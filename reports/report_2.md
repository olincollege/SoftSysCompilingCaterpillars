# Comp-lexity Static Checker and Code Generation
Rishita Sarin, Grant Miner, Abitamim Bharmal

## Project Goal
This project, we built on our our toy compiler project from last sprint and added static checking and code generation capabilities to it. We took the parser output to generate assembly code in x86. This assembly code can be put into pre-existing webpages such as https://godbolt.org/ to execute it. Our lower bound was to have a functional static check and add code generation for variable declaration, arithmetic operations with two operands and one operator, and if/else statements. Time permitting, our upper bound was be to execute the same for while loops. We were able to achieve both our lower bound and upper bound goals. 

## Learning Goals

We all shared the same learning goals this project. Our primary goal was to learn and gain experience in x86 assembly language. We were also hope to develop our skills of working in a team based software project with a special focus in delegation of tasks, keeping up with documentation, and maintaing communication within the team via regular syncs.

Rishita was originally also interested in pursuing the tasks related to being a PM on a software project team. However, as it turns out there are not too many PM related tasks within this team. We all mutually delegated tasks and maintained communication. Thereby, Rishita pivoted her learning goals to gain experience in writing code from scratch in C (in addition to learning about x86). 

Grant wanted to develop a moderate ability to translate code into assembly by hand, and he was looking forward to validating the code generation for the test files.

Abitamim wanted to learn assembly and how code changes can result in assembly changes. He also wanted to learn how to structure code generation to allow for efficient traversal of the syntax tree.

## Our Work

Stage 1 - Research
look at resources on what is assembly code, how to generate it, what is x86. 
read through and rewrote the code examples of code generation - toy compiler on github and a bunch of other open source compiler codes in different languages
videos as well on how registers work in assembly code

Research for static checker? 

Stage 2 - Static Checker
The purpose of a static checker is to detect and report any syntactic and semantic programming errors. Our static checker begins by traversing though a list of statements to make sure no variables are used before they are declared. If they are, there will be an error and the insertion will not work. For every variable in an expression, the static checker determines if it exists in a hash map, it if does, save the value to the variable struct. If the current value is a number, add it to the value list. Then, check the remaining part of the expression. 

Similarly, check if the left hand side and right hand side expressions are valid in order to validate a conditional. 
Validate all conditionals in the if and else statements to validate a branch. 
Validate the conditional for a while loop to validate it. 

 
Stage 3 - Code Generation
take the static checked parser output and convert it to assembly code
Varaibles are stored in a hash table
set up levels for reading assembly code
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
