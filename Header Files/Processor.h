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
    bool forward1;
    bool forward2;
    Core *cores[2] = {new Core(), new Core()};
    Processor()
    {
        memory1 = (char *)malloc(4000 * sizeof(char));
        memory2 = memory1 + 2000;
        tail1 = memory1;
        tail2 = memory1 + 2000 * sizeof(char);
        if (memory1 == NULL)
            std::cout << "memory not allocated";
        else
            std::cout << "memory allocated" << memory1 << std::endl;
    }
    void run()
    {

        // cores[0]->instruction_memory = instruction_memory1;
        cores[0]->run(instruction_memory1, memory1, forward1);
        cores[1]->run(instruction_memory2, memory2, forward2);
        // cores[0]->printReg();
        // cores[1]->printReg();
    }
    void print_regs()
    {
        std::cout << "--------------------CORE 1--------------------" << std::endl;
        // for (int i = 0; i < 50; i++)
        // {
        //     for(int j=0;j<200;j++){
        //         auto it = cores[0]->dispaly_vector[j].begin();
        //         int flag=0;
        //         for(int k=0;k<i;k++){
        //             it++;
        //             if(it==cores[0]->dispaly_vector[j].end()){
        //                 flag=1;
        //                 break;
        //             }
        //         }
        //         if(it<cores[0]->dispaly_vector[j].end() && flag==0){
        //             std::cout<<*it<<" ";
        //         }else{
        //             std::cout<<"  "<<" ";
        //         }
        //     }
        //     // for (auto it = cores[0]->dispaly_vector[i].begin(); it < cores[0]->dispaly_vector[i].end(); it++)
        //     // {
        //     //     std::cout<<*it<<" ";
        //     // }
        //     std::cout<<std::endl;
        // }
        std::cout << "Cycles: " << cores[0]->clock << std::endl;
        std::cout << "Stalls: " << cores[0]->stalls << std::endl;
        std::cout << "IPC: " << (float)cores[0]->instruction_count / cores[0]->clock << std::endl;
        std::cout << "hits: " << cores[0]->hits <<std::endl;
        std::cout << "misses: " << cores[0]->missess <<std::endl;
        cores[0]->cache->pirnt_cashe();
        std::cout << "registers after execution-->" << std::endl;
        for (int i = 0; i < 31; i++)
        {
            std::cout << "x" << i << ":  " << (cores[0]->regs[i]) << std::endl;
        }
        std::cout << "--------------------CORE 2--------------------" << std::endl;
        std::cout << "Cycles: " << cores[1]->clock << std::endl;
        std::cout << "Stalls: " << cores[1]->stalls << std::endl;
        std::cout << "IPC: " << (float)cores[1]->instruction_count / cores[1]->clock << std::endl;
        std::cout << "hits: " << cores[1]->hits <<std::endl;
        std::cout << "misses: " << cores[1]->missess <<std::endl;
        std::cout << "registers after execution-->" << std::endl;
        for (int i = 0; i < 31; i++)
        {
            std::cout << "x" << i << ":  " << cores[1]->regs[i] << std::endl;
        }
    }
};