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
    char *memory;
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
        memory = (char *)malloc(4000 * sizeof(char));
        tail1 = memory;
        tail2 = memory + 2000 * sizeof(char);
        if (memory == NULL)
            std::cout << "memory not allocated";
        else
            std::cout << "memory allocated at:" << memory << std::endl;
    }
    void run()
    {

        // cores[0]->instruction_memory = instruction_memory1;
        cores[0]->run(instruction_memory1, memory);
        std::cout << "Clocks: " << cores[0]->clock << std::endl;
        std::cout << "Stalls: " << cores[0]->stalls << std::endl;
        auto it = cores[0]->dispaly_vector.begin();
        int n = 0;
        for (it; it < cores[0]->dispaly_vector.end(); it++)
        {
            std::cout << *it << std::endl;
            if (*it == "-")
            {
                std::cout << "\r";
            }
            if (*it == "wb")
            {
                n++;
                for (int i = 0; i < n; i++)
                    std::cout << "  "<<std::endl;
            }
        }
        // cores[0]->printReg();
        // cores[1]->printReg();
    }
};