# Comp-lexity

Abitamim Bharmal, Grant Miner, Rishita Sarin

## Project Goal

Our team is hoping to dig deeper into the inner workings of compilers by building the first building blocks of one. We will be focusing on a very small subset of commands within both a language and an instruction set. 
We have found resources that guide us through making a compiler for languages very similar to the toy language we have created. We will create extensive documentation of these tutorials to make them easier to understand. We hope to use this content as a resource for those who are interested in the mechanics of compilers. 
Our basic toy compiler will be able to perform arithmetic functions namely addition, subtraction, multiplication, and division on floating numbers (one operation at a time - example 1 + 2 would yield 3) and assign numerical values to variables (example a = 4) as a lower bound. Our hope is that our lower bound compiler will lex, parse, and perform code generation. 
Our stretch goal is to develop if/else statement and while loop functionality to perform advanced operations using our compiler. The stretch goal compiler will lex and parse only. 

## Learning Goals

###Overarching Team Learning Goal
We have a basic understanding of the steps compilers take to get higher-level code down to machine code for execution. However, we do not have much insight into the mechanics by which each step is executed. Diving in deeper to the granularity of compilation will give us perspective to understand why our higher-level programs execute the way they do. We want to understand the architecture of lexers and parsers, and we want to explore how they interact with later stages in the process. We also hope to understand the high-level design decisions that go into creating a compiler.

### Individual Learning Goals

#### Rishita
In addition to the team goal, with this project I wanted to get more comfortable coding in C. For this broad goal, I decided to pursue two concrete paths: reading and writing C. There is value in being able to read code and understand its implementation. For this, I retyped and implemented a toy compiler walkthrough guide I was able to find online. As I typed the code, I also commented each file in order to better document my understanding of it. This work is pushed to the tutorials folder in this repo. There is also value in being able to write code from scratch. For this, I have taken upon the implementation of while loops in our compiler. There is a LLVM tutorial which explains the logic. However, there is minimal code and the code which is available is written in C++, so I have been working on translating this C++ code into C which has given me practice in writing C. 

I also wish to continue to build my developer skills in terms of efficiently gathering useful resources. I have always shyed away from using Stack Overflow because it has felt quite daunting, thus I would find myself struggling for a long period of time instead of just using my resources to my advantage. With this project, I took initiative to find initial resources and was able to successfully utilize an implementation of the toy compiler which my team is using as a base to build off of. For the LLVM tutorial C++ to C translation, I have started to use Stack Overflow and similar resources to help with syntax and related commands. This has allowed me to grow more comfortable with this resource and learn how to search efficiently to get useful results.  

#### Grant

#### Abitamim
My goals were to become more familiar with memory management and low-level
programming. 
I learned more about variable scoping, such as the fact that declaring a
variable inside a loop or if statement doesn't necessarily clear it, like would
be expected in python or other higher level languages. I learned this while
debugging my translation of the C++ version of the lexer. Now, I am learning
more about structs and using them in place of classes in the parser. A number of
different structs, along with unions, can be used in place of "nodes" to create
a AST.


## Getting Started: Resources

We have found several very useful resources on the workings of compilers, specifically on the lexer and parser stages. Our resources are located in [resources](../resources/links.txt).
We began this project by doing extensive research into the workings of compilers, and we have completed working through the tutorials we found. 

## Next Steps

We have a working compiler which can perform arithmetic and can assign numerical values to variables in the lexer and parser stages. The next steps as split by each team member as shown below. 

Abitamim - Build a parser based on the toy compiler but expanded to allow for
variable assignment, multi-character tokens, and conditionals and loops. 

Grant - Lexer and Parser implementation of if/else statements

Rishita - Lexer and Parser implementation of while loops 


Our goal is to complete all technical implementations of the compiler by Wednesday 3/9 and then spend the next two days documentating our work and hopefully submit this project by 3/11. 


## [ToDoist Link](https://todoist.com/app/project/2285969949)

## [Github Repo Link](https://github.com/olincollege/SoftSysCompilingCaterpillars)

