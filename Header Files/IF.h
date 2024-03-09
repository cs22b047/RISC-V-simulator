#include <iostream>
#include <vector>
#include <bitset>

class IF
{
public:
    IF()
    {
        std::cout << "in IF";
    }
    std::bitset<32> run(int pc,std::vector<std::bitset<32>>&instruction_memory){
       return instruction_memory[pc];
    }
};