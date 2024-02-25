# Phase 1
Here is our implimentation of a basic risc v  *dual core* simmulator built in c++. We have tested it by runnig two sorting algorithms simultaniously

To see the result clone the repo, and run the following commands in terminal
```console=
g++ -o parser.o -c Parser.cpp
g++ sim.cpp parser.o
./a.out
```
## Features Implimented

- add
- addi
- sub
- lw
- sw
- branch instructions(bne,beq,jal,blt....)
- slli
- ecall

## Design
![alt text](image.png)

## Minutes of meeting(to be held)
