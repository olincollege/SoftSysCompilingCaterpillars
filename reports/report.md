## Comp-lexity

Abitamim Bharmal, Grant Miner, Rishita Sarin
### Project Goal

Our team is hoping to dig deeper into the inner workings of compilers by building the first building blocks of one. We will be focusing on a very small subset of commands within both a language and an instruction set. We have found resources that guide us through making a compiler for languages very similar to the toy language we have created. We will create extensive documentation of these tutorials to make them easier to understand. We hope to use this content as a resource for those who are interested in the mechanics of compilers. Our basic toy compiler will be able to perform arithmetic functions namely addition, subtraction, multiplication, and division on floating numbers (one operation at a time - example 1 + 2 would yield 3) and assign numerical values to variables (example a = 4) as a lower bound. Our hope is that our lower bound compiler will lex, parse, and perform code generation. Our stretch goal is to develop if/else statement and while loop functionality to perform advanced operations using our compiler. The stretch goal compiler will lex and parse only.
Learning Goals
Overarching Team Learning Goal

We have a basic understanding of the steps compilers take to get higher-level code down to machine code for execution. However, we do not have much insight into the mechanics by which each step is executed. Diving in deeper to the granularity of compilation will give us perspective to understand why our higher-level programs execute the way they do. We want to understand the architecture of lexers and parsers, and we want to explore how they interact with later stages in the process. We also hope to understand the high-level design decisions that go into creating a compiler.

### Individual Learning Goals

#### Rishita

In addition to the team goal, with this project I wanted to get more comfortable coding in C. For this broad goal, I decided to pursue two concrete paths: reading and writing C. There is value in being able to read code and understand its implementation. For this, I retyped and implemented a toy compiler walkthrough guide I was able to find online. As I typed the code, I also commented each file in order to better document my understanding of it. This work is pushed to the tutorials folder in this repo. There is also value in being able to write code from scratch. For this, I have taken upon the implementation of while loops in our compiler. There is a LLVM tutorial which explains the logic. However, there is minimal code and the code which is available is written in C++, so I have been working on translating this C++ code into C which has given me practice in writing C.

I also wish to continue to build my developer skills in terms of efficiently gathering useful resources. I have always shyed away from using Stack Overflow because it has felt quite daunting, thus I would find myself struggling for a long period of time instead of just using my resources to my advantage. With this project, I took initiative to find initial resources and was able to successfully utilize an implementation of the toy compiler which my team is using as a base to build off of. For the LLVM tutorial C++ to C translation, I have started to use Stack Overflow and similar resources to help with syntax and related commands. This has allowed me to grow more comfortable with this resource and learn how to search efficiently to get useful results.

#### Grant

In Computer Architecture last semester, I spent some time on the far opposite end of the compilation process: understanding assembly code, and I wanted to explore the whole range of the process. The two compilers we experimented with, which are partially included in the /tutorials/grant folder, used different methods to implement the lexer and the parser. I have been digging into these two tutorials to try to understand why they are written differently. The LLVM compiler, notably, is in C++, which presents its own suite of challenges. I have never done extensive translation between languages before, so the process of breaking down the higher-level language into pieces and restructuring the code in C has been incredibly valuable for my learning.

I had originally hoped to make it to the code generation stage of compilation, but we rescoped in response to the translation hurdles. There is definitely more room for exploration if we decide to continue this project past its due date. I hope one day I will have built a compiler start to finish (even if it only works on a very limited instruction set).

#### Abitamim

My goals were to become more familiar with memory management and low-level programming. I became more experienced with memory allocation, since a variable declared in a function could be reallocated to the exact same spot when the function is called again, unlike what is be expected in python or other higher level languages. This fulfills the goal regarding memory management at some level, because I have to consider and account for memory at any location. I learned this while debugging my translation of the C++ version of the lexer.
Now, I am learning more about structs and using them in place of classes in the parser. A number of different structs, along with unions, can be used in place of "nodes" to create a AST. This will help me in the future creating more complicated yet well divided programs with the help of structs and unions to simulate some OO elements.
Getting Started: Resources

### Our Work

#### Stage 1 - Research

When we began this project, the team had minimal knowledge regarding the inner workings of a compiler. Therefore, the first step of the process was to do extensive research on toy compilers and subsequently their different components - primarily lexers and parsers. All our resources including walkthrough tutorials of basic arithmetic performing toy compilers are located in the resources tab. 

#### Stage 2 - Tutorials and Learning Curve

Once we had a conceptual understanding of compilers, we proceeded to walk through and implement the tutorials we had found. There were two main tutorials - an LLVM Kaleidoscope compiler infrastructure walkthrough in C++ and an open source toy compiler lecture in C. Both had different approaches to lexing and parsing with the LLVM tutorial being more advanced (with more edge cases taken into account) than the open source lecture. Abitamim focused on translating LLVM tutorial code from C++ to C. Meanwhile, Rishita and Grant independently followed the open source lecture and rewrote all code to ensure understanding of the material. Rishita also commented the code for a better understanding of future readers. These tutorials were focused on building a toy compiler which could perform arithmetic functions when given two operands and an operator (+,  -,  /,  *). These compiler tutorials walked through lexing, parsing, as well as code generation. These implementations can be found within the tutorials tab. 

#### Stage 3 - Our Implementation 

3.A. Rewrite the Syntax Tree
Once we had a deep understanding of compilers and were able to recreate a working toy compiler from lexing to code generation which could perform arithmetic functions, we decided to advance our compiler to be able to assign numerical values to variables, interpret if/else statements, and perform while loops. In order to add these functionalities to our compiler, we had to revisit our original syntax tree and logic from the two tutorials we followed. 

3.B. Split Work and Advance the Compiler
A majority of our project till this point lent itself to synchronous work and working on similar tasks as we ramped up. Upon rewriting the syntax tree, we scoped three main functions to add to the compiler and thereby split tasks based on these functions. This was a great learning experience for us as we navigated independent asynchronous work which required clear communication, openness to seeking help, and developing compatible code. We were successful in regular team check-ins and taking initiative to meet and ask clarifying questions. 
We split the tasks as follows: 
Abitamim built a parser based on the toy compiler but expanded it to allow for variable assignment, multi-character tokens, and conditionals and loops. Grant took lead on if/else statement lexer and parser implementation while Rishita took lead on while loop lexer and parser implementation. 
3.C. Rescoping
As we were approaching spring break, the team rescoped our goals. We realized that it would be a leap to have a functional code generation functionality in our compiler before break and would likely require working over break. Since we wanted to primarily disconnect from work over break, we revised our goal to have a functional lexer and parser compiler by the end of this project. Given the opportunity, we would like to continue developing this compiler and add code generation capability to it. 

3.D. Visualization
Abitamim can talk about this. 


