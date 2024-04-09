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
   bool branch_taken = false;
    EXE()
    {
        // std::cout << "in ID";
    }
    void run(int oppcode,int rs1,int rs2,int immediate,long int regs[],int rd,bool eof,bool datahazard){
        // std::cout<<"exe run"<<this->rs1<<this->rs2<<" "<<this->rd<<std::endl;
        std::cout<<"EXE ";
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
        if(oppcode==50||oppcode==53||oppcode==54||oppcode==60||oppcode==61){
            result=immediate+regs[rs1];
        }
        if(oppcode==59){
            result=pow(regs[rs1],immediate);
        }
        if (oppcode==55){
            if(regs[rs1]!=regs[rs2]){
                branch_taken=true;
            }
        }
        if (oppcode==56){
            if(regs[rs1]==regs[rs2]){
                branch_taken=true;
            }
        }
        if(oppcode==57){
            if(regs[rs2]>=regs[rs1]){
                branch_taken=true;
            }
        }
        if(oppcode==58){
            if(regs[rs2]<regs[rs1]){
                branch_taken=true;
            }
        }
        if(oppcode==62){
            branch_taken=true;
        }
    //    std::cout<<this->rd<<"/"<<this->immediate<<std::endl;                                                             
    }
};