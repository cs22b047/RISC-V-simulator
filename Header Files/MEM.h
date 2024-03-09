#include <iostream>

class MEM
{
public:
    MEM()
    {
        std::cout << "in MEM";
    }
    void run(int oppcode){
      if(oppcode==51||oppcode==52){
        return;
      }
    }
};