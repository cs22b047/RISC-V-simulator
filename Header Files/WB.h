#include <iostream>

class WB
{
public:
    bool eof = false;
    int rd=0;
    bool run_state = false;
    WB()
    {
        std::cout << "in WB";
    }
    void run(int rd, int result, long int regs[], int oppcode, bool eof,char* memory)
    {
        // std::cout << "wb run" << this->rd << std::endl;
        std::cout<<"WB ";
        this->eof = eof;
        this->rd = rd;
        run_state=false;
        if (oppcode == 51 || oppcode == 52 || oppcode == 50 || oppcode == 59)
        {
            regs[rd] = result;
        }
        if (oppcode == 53||oppcode==60)
        {
            regs[rd] = result;
        }
        if(oppcode==61){
            regs[rd]=(long int)(memory+result);
        }
    }
};