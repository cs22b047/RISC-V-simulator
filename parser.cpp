#include <iostream>
#include <vector>
#include <bitset>
#include <sstream>
class Processor
{
    std::vector<std::bitset<32>> instruction_memory;
    std::vector<int> data_memory;
    char* memory = (char*) calloc(4000,sizeof(char));
    char* tail1 = memory;

public:
    Processor(std::vector<std::bitset<32>> instruction_memory)
    {
        this->instruction_memory = instruction_memory;
    }
    /*void parse_memory_instruction(){
      int func7;
      int rs2;
      int rs1;
      int funct3;
      int rd;
      int oppcode;
      auto it=instruction_memory.begin();
      for(it;it<instruction_memory.end();it++){

      }
    }*/
    void parse_memory_instruction(std::string instruction)
    {
        std::vector<std::string> parts;
        std::string part;
        std::istringstream iss(instruction);
        while (iss >> part)
        {
            parts.push_back(part);
        }
        std::bitset<7> func7;
        std::bitset<5> rs2;
        std::bitset<5> rs1;
        std::bitset<3> funct3;
        std::bitset<5> rd;
        std::bitset<7> oppcode;
        std::bitset<32> final;
        std::bitset<12> immediate;
        auto it = parts.begin();
        if (*it == "add")
        {
            int x1 = get_reg(++it);
            int x2 = get_reg(++it);
            int x3 = get_reg(++it);
            func7 = 0;
            rs1 = x2;
            rs2 = x3;
            rd = x1;
            funct3 = 0;
            oppcode = 51;
            for (int i = 0; i < 7; i++)
            {
                final[i] = oppcode[i];
            }
            for (int i = 7; i < 12; i++)
            {
                final[i] = rd[i - 7];
            }
            for (int i = 12; i < 15; i++)
            {
                final[i] = funct3[i - 12];
            }
            for (int i = 15; i < 20; i++)
            {
                final[i] = rs1[i - 15];
            }
            for (int i = 20; i < 25; i++)
            {
                final[i] = rs2[i - 20];
            }
            for (int i = 25; i < 32; i++)
            {
                final[i] = func7[i - 25];
            }
            *(int*)tail1 = (int)final.to_ulong();
            tail1 = tail1 + sizeof(int);
        }
        if (*it == "sub")
        {
            int x1 = get_reg(++it);
            int x2 = get_reg(++it);
            int x3 = get_reg(++it);
            func7 = 32;
            rs1 = x2;
            rs2 = x3;
            rd = x1;
            funct3 = 0;
            oppcode = 51;
            for (int i = 0; i < 7; i++)
            {
                final[i] = oppcode[i];
            }
            for (int i = 7; i < 12; i++)
            {
                final[i] = rd[i - 7];
            }
            for (int i = 12; i < 15; i++)
            {
                final[i] = funct3[i - 12];
            }
            for (int i = 15; i < 20; i++)
            {
                final[i] = rs1[i - 15];
            }
            for (int i = 20; i < 25; i++)
            {
                final[i] = rs2[i - 20];
            }
            for (int i = 25; i < 32; i++)
            {
                final[i] = func7[i - 25];
            }
            *(int*)tail1 = (int)final.to_ulong();
            tail1 = tail1 + sizeof(int);
        }
        if (*it == "addi")
        {
            int x1 = get_reg(++it);
            int x2 = get_reg(++it);
            long int x3 = 0;
            for (int i = 0; i < (*it).length(); i++)
            {
                x3 = x3 * 10 + ((*it)[i] - 48);
            }
            immediate=x3;
            rs1 = x2;
            rd = x1;
            funct3 = 0;
            oppcode = 51;
            for (int i = 0; i < 7; i++)
            {
                final[i] = oppcode[i];
            }
            for (int i = 7; i < 12; i++)
            {
                final[i] = rd[i - 7];
            }
            for (int i = 12; i < 15; i++)
            {
                final[i] = funct3[i - 12];
            }
            for (int i = 15; i < 20; i++)
            {
                final[i] = rs1[i - 15];
            }
            for(int i=20;i<32;i++){
                final[i]=immediate[i-20];
            }
            *(int*)tail1 = (int)final.to_ulong();
            tail1 = tail1 + sizeof(int);
        }
    }
    int get_reg(std::vector<std::string>::iterator it)
    {
        int reg_id = 0;
        for (int i = 1; i < (*it).length(); i++)
        {
            reg_id = reg_id * 10 + ((*it)[i] - 48);
        }
        return reg_id;
    }
};