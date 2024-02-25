#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <string>
#include <cmath>
#include "./Core.h"
class Processor
{
public:
    char *memory;
    char *tail1;
    char *tail2;
    std::unordered_map<std::string, char *> label_map1;
    std::unordered_map<std::string, char *> label_map2;

    int clock = 0;
    Core *cores[2] = {new Core(), new Core()};
    Processor()
    {
        memory = (char *)malloc(4000 * sizeof(char));
        tail1 = memory;
        tail2 = memory+2000*sizeof(char);
        if (memory == NULL)
            std::cout << "memory not allocated";
        else
            std::cout << "memory allocated at:" << memory << std::endl;
    }
    void run()
    {
        while (cores[0]->execute(label_map1)||cores[1]->execute(label_map2))
        {
            clock++;
        }
        std::cout<<std::endl;
        cores[0]->printReg();
        cores[1]->printReg();
    }
    void parse(Core *core,std::unordered_map<std::string, char *> &label_map,char* &tail);
    void allocate_memory();
    void print_memory(char* ptr,char* tail);
    std::string trim(const std::string &s);
};