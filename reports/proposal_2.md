# Proposal Complex-ity (Continued)
### Rishita Sarin, Grant Miner, Abitamim Bharmal
## Previous Project Learning Experience
We had a really good learning experience last project in terms of technical skills as well as teaming skills, thus we have decided to work together again this project. We were able to successfully build a lexer and parser from scratch in C and learn more about the inner workings of a compiler. Our biggest hiccups last project came from our procrastination on documentation and irregular team syncs. The final report took us much longer than we anticipated primarily because we were so focused on building our compiler that we ended up with documentation on the back burner. In order to avoid this in the future, we will be documenting our work progress as we move along the project. Last project we also did not take initiative to have regular team syncs; we met whenever we wanted to touch base or had to clear up confusion. This worked for the most part, but also meant that since we were working at our own pace, it made it harder to ensure we were all on the same page. This time, we have already set up weekly sync times as well as working meetings to ensure clear communication and overall less stress. 

## Project Goal
This project, we are planning to build on our our toy compiler project from last time and add code generation capability to it. The idea is to take the output from the parser and output assembly code in x86. This assembly code can be put into pre-existing webpages such as https://godbolt.org/ to execute it. Our lower bound is to add code generation for variable declaration, arithmetic operations with 2 operands and 1 operator, and if/else statements. Time permitting, out upper bound would be to execute the same for while loops.

## Learning Goals
We all share the same learning goals this project. Our primary goal is to learn and gain experience in x86 assembly language. We also hope to develop our skills of working in a team based software project with a special focus in delegation of tasks, keeping up with documentation, and maintaing communication within the team via regular syncs. 

Rishita is also interested in pursuing the tasks related to being a PM on a software project team. IDK if this is actually possible given our project? 

## Resources
We've found some lectures on x86 that we hope to look through and take notes on to build a basic understanding of this assembly language. We also have a toy compiler example of code generation as a starting point  to work through. 
Since all of us have little experience in this space, we would appreciate any other resources available to the teaching team. 

x86 resouces: https://www.cs.utexas.edu/~pingali/CS377P/2021sp/lectures/x86Compilers.pdf, https://www.cs.virginia.edu/~evans/cs216/guides/x86.html, https://en.wikibooks.org/wiki/X86_Disassembly/Assemblers_and_Compilers
Toy compiler: https://cop3402fall20.github.io/lectures/03_toy_compiler.html
How Code Generation Works: https://www.tutorialspoint.com/compiler_design/compiler_design_code_generation.htm

## Next Steps
We all have little experience when it comes to x86. We will all go through the x86 lectures to build a foundation for this work. 
Then, we will all read through and understand code generation toy compiler code.
Grant has some experience working in this space due to his background in Computer Architecture. He will refresh his memory and share those resources with us. 
Abitamim will be working on static checking. If the parser raises an error while doing static analysis, we will consider is done. 
Grant will translate our test file into assembly code by hand. 

We had a sync set up for Monday and Wednesday where we will discuss out findings and ensure we are all on the same page with our understanding of the material.
