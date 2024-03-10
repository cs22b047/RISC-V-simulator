#include <iostream>

class WB
{
public:
    bool eof = false;
    int rd;
    bool run_state = false;
    WB()
    {
        std::cout << "in WB";
    }
    void run(int rd, int result, long int regs[], int oppcode, bool eof)
    {
        std::cout << "wb run" << this->rd << std::endl;

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
    }
};