#include <iostream>
#include <bitset>
#include <vector>
class ID
{

public:
    int x1;
    int x2;
    int oppcode;
    int rd;
    int immediate;
    // int immediate;
    ID()
    {
        std::cout << "in ID";
    }
    void run(std::bitset<32> instruction,int regs[])
    {
        std::bitset<7> oppcode;
        std::bitset<5> rd;
        std::bitset<5> rs1;
        std::bitset<5> rs2;
        for (int i = 0; i < 7; i++)
        {
            oppcode[i] = instruction[i];
        }
        if (oppcode == 51 || oppcode == 52)
        {

            for (int i = 7; i < 12; i++)
            {
                rd[i - 7] = instruction[i - 7];
            }
            for (int i = 15; i < 20; i++)
            {
                rs1[i - 15] = instruction[i];
            }
            for (int i = 20; i < 25; i++)
            {
                rs2[i - 20] = instruction[i];
            }
        }
        
        this->oppcode=(int)oppcode.to_ullong();
        this->rd=(int)rd.to_ullong();
        this->x1=regs[(int)rs1.to_ullong()];
        this->x2=regs[(int)rs2.to_ullong()];

        

    }

};