#include <iostream>
#include <string>
using namespace std;
class Core{
    public:
        long int regs[32];
        long int pc;
        string program[];
    
};
class processor{
    public:
        int* memory = (int*)malloc(4096);
        int clock =0;
        Core cores[2] = {Core(),Core()};


};
int main(){

}
