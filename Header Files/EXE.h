#include <iostream>

class EXE
{
public:
   int result;
   int oppcode;
   int rd;
   bool eof=false;
   int rs1;
   int rs2;
   int immediate;
   bool stall= false;
   bool run_state = false;
    EXE()
    {
        std::cout << "in ID";
    }
    void run(int oppcode,int rs1,int rs2,int immediate,long int regs[],int rd,bool eof){
        std::cout<<"exe run"<<this->rs1<<this->rs2<<" "<<this->rd<<std::endl;

        this->oppcode=oppcode;
        this->rd=rd;
        this->eof=eof;
        this->rs1=rs1;
        this->rs2=rs2;
        this->immediate=immediate;
        run_state=false;
        if(oppcode==51||oppcode==52){
           if(oppcode==51){
            result=regs[rs1]+regs[rs2];
           }else{
            result=regs[rs1]-regs[rs2];
           }
        }
        if(oppcode==50||oppcode==53||oppcode==54||oppcode==60){
            result=immediate+regs[rs1];
        }
        if(oppcode==59){
            result=pow(regs[rs1],immediate);
        }
        
    }
};