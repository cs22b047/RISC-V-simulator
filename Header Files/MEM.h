#include <iostream>

class MEM
{
public:
    int oppcode;
    int result;
    int rd;
    bool eof=false;
    bool stall =false;
    bool run_state=false;
    MEM()
    {
        // std::cout << "in MEM";
    }
    void run(int oppcode, int result, int rd, bool eof,bool stall,int immediate,char* &memory)
    {
        // std::cout<<"mem run"<<this->rd<<std::endl;
        std::cout<<"MEM ";
        this->stall = stall; 
        this->oppcode = oppcode;
        this->result = result;
        this->rd = rd;
        this->eof=eof;
        run_state = false;
        // std::cout<<this->result;
        if (oppcode == 51 || oppcode == 52||oppcode==59||oppcode==50||oppcode==60)
        {

            return;
        }
        if(oppcode==53){
            // std::cout<<" "<<result<<std::endl;
            this->result=*(memory+result);
            // std::cout<<result<<std::endl;

        }
        // if(oppcode==54){
        //     *(memory+result)=regs[rd];
        // }
        
    }
};