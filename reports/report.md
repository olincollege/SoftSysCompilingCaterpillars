# Comp-lexity

### Abitamim Bharmal, Grant Miner, Rishita Sarin

## Project Goal
Our team was hoping to dig deeper into the inner workings of compilers by building the first building blocks of one. We were focusing on a very small subset of commands within both a language and an instruction set. We found resources that guided us through making a compiler for languages very similar to the toy language we have created. We created documentation of these tutorials to make them easier to understand. We hope to use this content as a resource for those who are interested in the mechanics of compilers. 
Our basic toy compiler performs arithmetic functions namely addition, subtraction, multiplication, and division on floating numbers (one operation at a time - example 1 + 2 would yield 3), assigns numerical values to variables (example a = 4), and can interpret if/else statements as well as while loops. 

At the beginning of this project, we had a basic understanding of the steps compilers take to get higher-level code down to machine code for execution. However, we did not have much insight into the mechanics by which each step was executed. Diving in deeper to the granularity of compilation gave us perspective to understand why our higher-level programs execute the way they do. We wanted to understand the architecture of lexers and parsers, and we wanted to explore how they interacted with later stages in the process. We also hoped to understand the high-level design decisions that go into creating a compiler with this project.


## Individual Learning Goals

### Rishita

In addition to the team goal, with this project I wanted to get more comfortable coding in C. For this broad goal, I decided to pursue two concrete paths: reading and writing C. There is value in being able to read code and understand its implementation. For this, I retyped and implemented a toy compiler walkthrough guide I was able to find online. As I typed the code, I also commented on each file in order to better document my understanding of it. This work is pushed to the tutorials folder in this repo. There is also value in being able to write code from scratch. For this, I took upon the implementation of while loops in our compiler. There is a LLVM tutorial which explains the logic. However, there is minimal code and the code which is available is written in C++ or BASIC, so I translated this C++/ BASIC code into C which gave me practice in writing C.

I also wished to continue to build my developer skills in terms of efficiently gathering useful resources. I have always shied away from using Stack Overflow because it has felt quite daunting, thus I would find myself struggling for a long period of time instead of just using my resources to my advantage. With this project, I took initiative to find initial resources and was able to successfully utilize an implementation of the toy compiler which my team is using as a base to build off of. For the LLVM tutorial C++ to C translation, I have started to use Stack Overflow and similar resources to help with syntax and related commands. This has allowed me to grow more comfortable with this resource and learn how to search efficiently to get useful results.


### Grant

In Computer Architecture last semester, I spent some time on the far opposite end of the compilation process: understanding assembly code, and I wanted to explore the whole range of the process. The two compilers we experimented with, which are partially included in the /tutorials/grant folder, used different methods to implement the lexer and the parser. I have been digging into these two tutorials to try to understand why they are written differently. The LLVM compiler, notably, is in C++, which presents its own suite of challenges. I have never done extensive translation between languages before, so the process of breaking down the higher-level language into pieces and restructuring the code in C has been incredibly valuable for my learning.

I had originally hoped to make it to the code generation stage of compilation, but we rescoped in response to the translation hurdles. There is definitely more room for exploration if we decide to continue this project past its due date. I hope one day I will have built a compiler start to finish (even if it only works on a very limited instruction set).

### Abitamim

My goals were to become more familiar with memory management and low-level programming. I became more experienced with memory allocation, since a variable declared in a function could be reallocated to the exact same spot when the function is called again, unlike what is be expected in python or other higher level languages. This fulfills the goal regarding memory management at some level, because I have to consider and account for memory at any location. I learned this while debugging my translation of the C++ version of the lexer.

Now, I am learning more about structs and using them in place of classes in the parser. A number of different structs, along with unions, can be used in place of "nodes" to create a AST. This will help me in the future creating more complicated yet well divided programs with the help of structs and unions to simulate some OO elements.
Getting Started: Resources

## Our Work

### Stage 1 - Research

When we began this project, the team had minimal knowledge regarding the inner workings of a compiler. Therefore, the first step of the process was to do extensive research on toy compilers and subsequently their different components - primarily lexers and parsers. All our resources including walkthrough tutorials of basic arithmetic performing toy compilers are located in the [resources tab](https://github.com/olincollege/SoftSysCompilingCaterpillars/tree/main/resources). 

### Stage 2 - Tutorials and Learning Curve

Once we had a conceptual understanding of compilers, we proceeded to walk through and implement the tutorials we had found. There were two main tutorials - an LLVM Kaleidoscope compiler infrastructure walkthrough in C++ and an open source toy compiler lecture in C. Both had different approaches to lexing and parsing with the LLVM tutorial being more advanced (with more edge cases taken into account) than the open source lecture. Abitamim focused on translating LLVM tutorial code from C++ to C. Meanwhile, Rishita and Grant independently followed the open source lecture and rewrote all code to ensure understanding of the material. Rishita also commented the code for a better understanding of future readers. These tutorials were focused on building a toy compiler which could perform arithmetic functions when given two operands and an operator (+,  -,  /,  *). These compiler tutorials walked through lexing, parsing, as well as code generation. These implementations can be found within the [tutorials tab.](https://github.com/olincollege/SoftSysCompilingCaterpillars/tree/main/tutorials) 

### Stage 3 - Our Implementation

#### 3.A. Rewrite the Syntax Tree
Once we had a deep understanding of compilers and were able to recreate a working toy compiler from lexing to code generation which could perform arithmetic functions, we decided to advance our compiler to be able to assign numerical values to variables, interpret if/else statements, and perform while loops. In order to add these functionalities to our compiler, we had to revisit our original syntax tree and logic from the two tutorials we followed. After we designed the new structure, Abitamim adapted the lexer code from the LLVM tutorial to work with the new features.

#### 3.B. Split Work and Advance the Compiler
A majority of our project till this point lent itself to synchronous work and working on similar tasks as we ramped up. Upon rewriting the syntax tree, we scoped three main functions to add to the compiler and thereby split tasks based on these functions. This was a great learning experience for us as we navigated independent asynchronous work which required clear communication, openness to seeking help, and developing compatible code. We were successful in regular team check-ins and taking initiative to meet and ask clarifying questions. We split the tasks as follows: Abitamim built a parser inspired by the toy compiler but written to allow for variable assignment, multi-character tokens, and conditionals and loops. Rishita took the lead in documentation, commenting, and validation. Grant took the lead in overall architecture and testing.

#### 3.C. Final Lexer and Parser

##### Lexer

Our Lexer reads one character at a time and assigns it a token categorizing it for the parser. Tokens are in a struct so we can save all the information regarding each token (various data types) in one place. Mainly we want to save the type of input and any value associated with it. 

If the character is a blank space or open/close bracket or # (a comment), lexer ignores it and moves on to the next character without assigning it a token. On the other hand, if the character is indicitive of End of File, an end token is created. 

If the first character read is an alphabet followed by alphanumerics, it is considered a variable token. However, if the first character is a number, the next characters must be numbers or a decimal point to be considered a number token. (Please note, for the sake of simplicity we chose to ignore the case where the first character is a number followed by aphanumerics). 

Finally, if "WHILE" or "ENDWHILE" are detected, a while loop token is generated while if "IF", "ELSE", or "ENDIF" are detected, a conditional token is generated. 

These tokens are then to be used by our parser. 

##### Parser 

Our parser looks at one token at a time and creates an abstract syntax tree interpreting the tokens lexed from the source code. The different components of a parser are as follows: 

1) An expression is lhs (left hand side) operand + operator + rhs (right hand side) operand.  (ex. x + 4)

2) A statement is a value or variable + equal sign + rhs (right hand side) operand.   (ex. y = 4)

3) A conditional is a lhs(left hand side) expression + comparator + rhs (right hand side) expression. (ex. if x + 4 > y + 1)

4) A branch is a conditional + list of statements which would be completed if the if statement is true + (if there is an "ELSE" statement, add another branch to parse through its list of statements).

5) A while = conditional + list of statements which would be completed till the while loop condition is considered true.  

Below is a syntax tree generated from a parser. 

##### Our Output 
![test3_visualization](https://user-images.githubusercontent.com/56645125/159417234-f07c2d6b-cf0d-47d1-8b9a-39ac2daf89b4.png)

#### 3.D. Rescoping
As we were approaching spring break, the team rescoped our goals. We realized that it would be a leap to have a functional code generation functionality in our compiler before break and would likely require working over break. Since we wanted to primarily disconnect from work over break, we revised our goal to have a functional lexer and parser compiler by the end of this project. Given the opportunity, we would like to continue developing this compiler and add code generation capability to it, along with different variable types and functions.

#### 3.E. Visualization
To see the tree as a tree, rather than a text output, Abitamim wrote a visualization script using Python and NetworkX that converted the output from the parser into a tree. This allowed for additional validation, ensuring that the tree we wanted to create was the tree that was created. It effectively recreated the parser in Python, but gradually created the tree as it read the parser output.

## Design Decisions 
1. We decided to separate the tokens for comparators and operators, even though both were single character tokens. In the lexer, this added slight complexity in deciding what type of token to return. However, in the parser, this resulted in less comparisons and simpler code, because we could check the type of the token (as a comparator or operator) without having to enter the actual value.

2. A design decision that was incorrect was using a different end statement for loops and conditionals, 'endif' and 'endwhile' respectively. This was created because we thought the language would have an easier to read syntax if we could see which statement was ending. However, using a single end statement would have the same effect, since only the innermost loop/conditional can end in a valid syntax. This would have made the parser slightly simpler, since there would be no need to check if the correct end statement was used.

3. We put deep copy functions, which accepted variables (intended for stack variables) and turned them into otherwise identical heap variables. This abstraction made the parser simpler because there were far fewer mallocs present, if at all. Only calling the appropriate deep copy function(s) was needed.

4. We made a few decisions regarding syntax to simplify our parsing. We opted to use the end statements for if and while statements rather than indentation to avoid dealing with whitespace delimiting. 

5. For expressions, we decided to ignore the order of operations so we would not have to know ahead of time what other operations are in the line. This made our parsing much easier for our iterative style.

6. Lastly, we opted to not use parentheses to delimit the conditional statements in our branches and loops. Using our functionality to check for new lines, we delimited the conditionals with the “if,” “else,” or “while” and the new line character. This mirrors the behavior of Python, and reusing other functionality we had created helped us simplify parsing.

## Reflection

### Grant
Most of my learning occurred in the earlier stages of the project. I was able to dive into translation between C++ and C, and I was also able to develop a better understanding of how data structures transfer between the two. At the close of the project, I gained a much greater understanding of implementing automation on larger projects. In the future I hope to learn more about managing projects, and I plan on investigating CMake and other automation tools for delivering software.


### Abitamim
I was able to more comfortably work with memory by praticing when writing the
parser, especially the deep_copy functions. In implementing a parser with large
amounts of recursion, I became better at thinking about and visualizing
problems, since I could visualize the stack, what needs to be returned to
accomplish certain goals, even with low level programming. As a bonus, when
writing the visualizer, I learned more about passing references by value (making
a copy of the reference) and how to manipulate data with that. This learning
will also carry over to C. Overall, I accomplished my learning goals of becoming
more familiar with memory management and low level programming.

