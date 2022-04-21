# Comp-lexity Project Update 2
Rishita Sarin, Grant Miner, Abitamim Bharmal

## Project Goal
This project, we are planning to build on our our toy compiler project from last time and add code generation capability to it. The idea is to take the output from the parser and output assembly code in x86. This assembly code can be put into pre-existing webpages such as https://godbolt.org/ to execute it. Our lower bound is to add code generation for variable declaration, arithmetic operations with 2 operands and 1 operator, and if/else statements. Time permitting, out upper bound would be to execute the same for while loops.

## Learning Goals

We all share the same learning goals this project. Our primary goal is to learn and gain experience in x86 assembly language. We also hope to develop our skills of working in a team based software project with a special focus in delegation of tasks, keeping up with documentation, and maintaing communication within the team via regular syncs.

Rishita was originally also interested in pursuing the tasks related to being a PM on a software project team. However, as it turns out there are not too many PM related tasks within this team. We have all mutually delegated tasks and maintained communication. Thereby, Rishita has pivoted her learning goals to gain experience in writing code from scratch in C (in addition to learning about x86). 

Grant has wanted to develop a moderate ability to translate code into assembly by hand, and he is looking forward to validating the code generation for the test files.

Abitamim wants to learn assembly and how code changes can result in assembly changes. He also wants to learn how to structure code generation to allow for efficient traversal of the syntax tree.

3) What have you done to get started?  Have you found the resources you need, do you have a plan to find them, or do you need help?  If you found any resources you think I should add to the list on the class web page, please email them to me.

Abitamim has developed a static checker to validate the output from the parser. Meanwhile Grant has written assembly code for our test file (test3) by hand and developed an architecture for the desired code generation output. Rishita has been working on developing the assembly code generation code by translating LLVM code. There have been hiccups during this process as LLVM does not translate to C as effectively as she had originally thought, therefore her current focus is to write the code from scratch. 

We currently have all the resources we would need and are on track to complete our project by the deadline. 

4) What are you working on now?  Describe at least three concrete tasks that you are working on, and identify which members of the team are working on them.  For each one, what is the "definition of done"; that is, what will you produce to demonstrate that the task is done?

Rishita is working on code generation for expressions and statements.
Grant is working on code generation for if/else statements. 
