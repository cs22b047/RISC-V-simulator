# Phase 2
Here is our implimentation of a basic risc v  *dual core* simmulator built in c++. We have tested it by runnig two sorting algorithms simultaniously

To see the result clone the repo, and run the following commands in terminal
```console=
g++ -o parser.o -c Parser.cpp
```
```console=
g++ sim.cpp parser.o
```
```console=
./a.out
```
## Features Implimented

- 32 bit instruction generation
- encoding instructions
- decoding instructions
- pipeline implementation
- implementation of stalls
- branch predection(branch always not taken)
- clock cycle calculation

## Design
![alt text](image.png)

## Key design decisions

- improvement of parser by using 32 bit bitset to encode and decode instructions
- pipeline implementation by using each stage as an object
- predecting hazards by checking registors involved in first three instuctions
- creating a branch predictor by considering branch always not taken
  

## Minutes of meeting

**Day 1 (March 2): 32-bit Instruction Generation**
- Design and implement basic instruction generation for arithmetic and logic operations.

**Day 2 (March 5): Pipeline Implementation**
- Design and implement the basic pipeline structure.

**Day 3 (March 6): Implementation of Stalls**
- Integrate stall mechanisms into the pipeline to resolve hazards.

**Day 4 (March 8): Refinement and Debugging**
- Refine the implementation and debug any issues.

**Day 5 (March 10): Final Testing and Documentation**
- Conduct comprehensive testing and document the implementation.
