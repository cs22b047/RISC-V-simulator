#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;
class Core{
    private:
        long int regs[32];
        long int pc;
        string instruction;
        public:
        Core(){
            for(int i=0;i<32;i++){
                regs[i]=0;
            }
            pc = 0;
        }
        void execute(int* memory,string instruction){
            this->instruction=instruction;
            vector<string> parts;
            string part;
            istringstream iss(instruction);
            while(getline(iss,part,' ')){
                parts.push_back(part);
            }
            auto it = parts.begin();
            if(*it=="addi") execute_addi(it);
            if(*it=="add") execute_add(it);
            if(*it=="sub") execute_sub(it);
            if(*it=="lw") execute_lw(it);
            if(*it=="sw") execute_sw(it);
            if(*it=="jal") execute_jal(it);
            if(*it=="bne") execute_bne(it);
            if(*it=="beq") execute_beq(it);
        }
        int get_reg(vector<string>::iterator it){
            int reg_id=0;
            for(int i=1;i<(*it).length();i++){
                reg_id = reg_id*10 + ((*it)[i]-48);
            }
            return reg_id;
        }
        void execute_addi(vector<string>::iterator it){
            int x1 = get_reg(++it);
            int x2 = get_reg(++it);
            it++;
            long int x3 = 0;

            for(int i=0;i<(*it).length();i++){
                x3 = x3*10 + ((*it)[i]-48);
            }
            regs[x1] = regs[x2] + x3; 
        }
        void execute_add(vector<string>::iterator it){
            int x1 = get_reg(++it);
            int x2 = get_reg(++it);
            int x3 = get_reg(++it);
            regs[x1] = regs[x2] + regs[x3];
        }   
        void execute_sub(vector<string>::iterator it){
            int x1 = get_reg(++it);
            int x2 = get_reg(++it);
            int x3 = get_reg(++it);
            regs[x1] = regs[x2] - regs[x3];
        }
        void execute_lw(vector<string>::iterator it){

            cout<<"exe_addi";
        }
        void execute_sw(vector<string>::iterator it){
            cout<<"exe_addi";
        }
        void execute_jal(vector<string>::iterator it){
            cout<<"exe_addi";
        }
        void execute_bne(vector<string>::iterator it){
            cout<<"exe_addi";
        }
        void execute_beq(vector<string>::iterator it){
            cout<<"exe_addi";
        }
        void printReg(){
            for(int i=0;i<32;i++){
                cout<<"x"<<(i)<<":    "<<regs[i]<<endl;
            }
        }
};

class Processor{
    public:
        int* memory = (int*)malloc(4096);
        int clock = 0;
        ifstream file_1,file_2;
        string instruction_1,instruction_2;
        Core *cores[2] = {new Core(),new Core()};
        void run(){
            while(getline(file_1,instruction_1)){
                cores[0]->execute(memory,instruction_1);
            }
            cores[0]->printReg();
        }

};
int main(){ 
    Processor sim;

    sim.file_1.open("/home/tilak/Projects/Risc-v_sim/program1.txt");
    sim.file_2.open("/home/tilak/Projects/Risc-v_sim/program2.txt");
    sim.run();
    return 0;
}
