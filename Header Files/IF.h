#include <iostream>
#include <vector>
#include <bitset>

class IF
{
public:
    std::bitset<32> instruction;
    bool eof = false;
    IF()
    {
        // std::cout << "in IF";
    }
    void run(int &pc, std::vector<std::bitset<32>> &instruction_memory)
    {
        // std::cout << "if run" << std::endl;
        std::cout<<"IF ";
        if (pc >= instruction_memory.size() - 1)
        {
            eof = true;
            this->instruction = instruction_memory[pc];
            pc++;
            return;
        }
        else
        {
            this->instruction = instruction_memory[pc];
            pc++;
        }
    }
};