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
    bool eof = false;
    bool run_state = false; 
    // int immediate;
    ID()
    {
        std::cout << "in ID";
    }
    void run(std::bitset<32> instruction, long int regs[], bool eof)
    {
        std::cout << "id run" << this->x1 << " " << this->x2 << " " << this->rd << std::endl;
        this->eof = eof;
        std::bitset<7> oppcode;
        std::bitset<5> rd;
        std::bitset<5> rs1;
        std::bitset<5> rs2;
        std::bitset<12> immediate;
        run_state = false;
        for (int i = 0; i < 7; i++)
        {
            oppcode[i] = instruction[i];
        }
        if (oppcode == 51 || oppcode == 52)
        {

            for (int i = 7; i < 12; i++)
            {
                rd[i - 7] = instruction[i];
            }
            for (int i = 15; i < 20; i++)
            {
                rs1[i - 15] = instruction[i];
            }
            for (int i = 20; i < 25; i++)
            {
                rs2[i - 20] = instruction[i];
            }
            this->oppcode = (int)oppcode.to_ullong();
            this->rd = (int)rd.to_ullong();
            this->x1 = (int)rs1.to_ullong();
            this->x2 = (int)rs2.to_ullong();
        }
        if (oppcode == 50||oppcode==59||oppcode==53||oppcode==54||oppcode==60)
        {
            for (int i = 7; i < 12; i++)
            {
                rd[i - 7] = instruction[i];
            }
            for (int i = 15; i < 20; i++)
            {
                rs1[i - 15] = instruction[i];
            }
            for (int i = 20; i < 32; i++)
            {
                immediate[i - 20] = instruction[i];
            }
            this->oppcode=(int)oppcode.to_ullong();
            this->immediate=(int)immediate.to_ullong();
            this->rd=(int)rd.to_ullong();
            this->x1=(int)rs1.to_ullong();


        }
        


    }
};