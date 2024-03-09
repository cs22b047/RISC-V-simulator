#include <iostream>

class WB
{
public:
    bool eof=false;
    WB()
    {
        std::cout << "in WB";
    }
    void run(int rd,int result,long int regs[],int oppcode,bool eof){
       this->eof = eof;
       if(oppcode==51||oppcode==52){
        regs[rd]=result;
       }
        std::cout<<"wb run"<<std::endl;

    }
};