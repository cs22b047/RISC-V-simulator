#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <string>
#include <cmath>
#include <bitset>
#include "./Core.h"
class Processor
{
public:
    char *memory1;
    char *memory2;
    char *tail1;
    char *tail2;
    std::unordered_map<std::string, long int> label_map1;
    std::unordered_map<std::string, long int> label_map2;
    std::vector<std::bitset<32>> instruction_memory1;
    std::vector<std::bitset<32>> instruction_memory2;
    int clock = 0;
    Core *cores[2] = {new Core(), new Core()};
    Processor()
    {
        memory1 = (char *)malloc(4000 * sizeof(char));
        memory2=memory1+2000;
        tail1 = memory1;
        tail2 = memory1 + 2000 * sizeof(char);
        if (memory1 == NULL)
            std::cout << "memory not allocated";
        else
            std::cout << "memory allocated at:" << memory1 << std::endl;
    }
    void run()
    {

        // cores[0]->instruction_memory = instruction_memory1;
        cores[0]->run(instruction_memory1, memory1);
        cores[1]->run(instruction_memory2, memory2);
        std::cout << "Clocks: " << cores[0]->clock << std::endl;
        std::cout << "Stalls: " << cores[0]->stalls << std::endl;

        std::cout << "Clocks: " << cores[1]->clock << std::endl;
        std::cout << "Stalls: " << cores[1]->stalls << std::endl;
        // cores[0]->printReg();
        // cores[1]->printReg();
    }
    void print_regs(){
        for(int i=0;i<31;i++){
            std::cout<<"x"<<i<<":  "<<cores[0]->regs[i]<<std::endl;
        }
        for(int i=0;i<31;i++){
            std::cout<<"x"<<i<<":  "<<cores[1]->regs[i]<<std::endl;
        }
    }
};