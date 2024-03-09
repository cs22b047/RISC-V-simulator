#include <iostream>

class EXE
{
public:
   int result;
   int oppcode;
   int rd;
   bool eof=false;
    EXE()
    {
        std::cout << "in ID";
    }
    void run(int oppcode,int rs1,int rs2,int immediate,long int regs[],int rd,bool eof){
        this->oppcode=oppcode;
        this->rd=rd;
        this->eof=eof;
        if(oppcode==51||oppcode==52){
           if(oppcode==51){
            result=rs1+rs2;
           }else{
            result=rs1-rs2;
           }
        }
        std::cout<<"exe run"<<std::endl;
    }
};