#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <string>
#include <cmath>
// using namespace std;
#include "../Header Files/Processor.h"
int main()
{
    Processor *sim = new Processor();

    sim->cores[0]->program_file.open("/home/tilak/Projects/Risc-v_sim/Test files/program1.txt");
    sim->cores[1]->program_file.open("/home/tilak/Projects/Risc-v_sim/Test files/program2.txt");
    sim->parse(sim->cores[0],sim->label_map1,sim->tail1);
    sim->parse(sim->cores[1],sim->label_map2,sim->tail2);
    // sim->print_memory();
    sim->run();

        sim->print_memory(sim->memory,sim->tail1);
        std::cout<<std::endl;
        sim->print_memory((sim->memory)+2000,sim->tail2);
    return 0;
}
