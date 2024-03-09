#include <iostream>

class EXE
{
public:
   int result;
    EXE()
    {
        std::cout << "in ID";
    }
    void run(int oppcode,int rs1,int rs2,int immediate,int regs[]){
        if(oppcode==51||oppcode==52){
           if(oppcode==51){
            result=rs1+rs2;
           }else{
            result=rs1-rs2;
           }
        }
    }
};