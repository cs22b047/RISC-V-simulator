#include <iostream>

class MEM
{
public:
    int oppcode;
    int result;
    int rd;
    bool eof=false;
    MEM()
    {
        std::cout << "in MEM";
    }
    void run(int oppcode, int result, int rd, bool eof)
    {
        this->oppcode = oppcode;
        this->result = result;
        this->rd = rd;
        this->eof=eof;
        if (oppcode == 51 || oppcode == 52)
        {
            return;
        }
        std::cout<<"mem run"<<std::endl;
    }
};