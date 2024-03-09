#include <iostream>

class WB
{
public:
    WB()
    {
        std::cout << "in WB";
    }
    void run(int rd,int result,int regs[],int oppcode){
       if(oppcode==51||oppcode==52){
        regs[rd]=result;
       }
    }
};