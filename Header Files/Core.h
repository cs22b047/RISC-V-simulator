#include <iostream>
#include <string>
#include <vector>
#include <./IF.h>
#include <./ID.h>
#include <./EXE.h>
#include <./MEM.h>
#include <./WB.h>

class Core
{
public:
    long int regs[32];
    int pc = 0;
    IF *_if = new IF();
    ID *id = new ID();
    EXE *exe = new EXE();
    MEM *mem = new MEM();
    WB *wb = new WB();
    std::vector<std::string> dispaly_vector;
    int clock = 0;
    int stalls = 0;
    int clock2 = 0;
    int clock3 = 0;
    bool datahazard = false;
    bool datahazard1 = false;
    bool detect(int rd, int rs1, int rs2)
    {
        return (rd == rs1) || (rd == rs2);
    }
    bool label = false;
    void run(std::vector<std::bitset<32>> &instruction_memory, char *memory)
    {
        auto it = instruction_memory.begin();
        for (it; it < instruction_memory.end(); it++)
        {
            std::cout << *it << std::endl;
        }
        while (!wb->eof)
        {
            datahazard = (detect(exe->rd, id->x1, id->x2) && (clock >= 3));
            datahazard1 = (detect(mem->rd, id->x1, id->x2) && (clock >= 4));

            if (datahazard || datahazard1)
            {
                std::cout << "data hazard" << std::endl;
                dispaly_vector.push_back("--");
                stalls++;
                exe->stall = true;
            }
            if (detect(wb->rd, id->x1, id->x2))
            {
                std::cout << "hazard over" << std::endl;
                if(datahazard1||datahazard){
                    dispaly_vector.pop_back();
                    stalls--;
                }
                exe->stall = false;
            }
            if (id->oppcode == 53 && id->x1 == 0)
            {
                std::cout << "lw hazard"<<std::endl;
                stalls++;
                exe->stall = true;
                clock2++;
            }
            if (clock2 == 4)
            {
                clock2 = 0;
                exe->stall = false;
            }
            if (clock >= 4 && wb->run_state)
            {
                dispaly_vector.push_back("wb");
                wb->run(mem->rd, mem->result, regs, mem->oppcode, mem->eof);
            }
            if (clock >= 3 && !mem->eof && !mem->stall && mem->run_state){
                dispaly_vector.push_back("mem");
                mem->run(exe->oppcode, exe->result, exe->rd, exe->eof, exe->stall, exe->immediate, memory);
                wb->run_state=true;
            }
            if (clock >= 2 && !exe->eof && !exe->stall && exe->run_state)
            {
                dispaly_vector.push_back("exe");
                exe->run(id->oppcode, id->x1, id->x2, id->immediate, regs, id->rd, id->eof);
                mem->stall = false;
                mem->run_state=true;
            }

            if (clock >= 1 && !(id->eof) && !exe->stall && id->run_state)
            {
                dispaly_vector.push_back("id");
                id->run(_if->instruction, regs, _if->eof);
                exe->run_state = true;
            }
            if (!_if->eof && !exe->stall)
            {
                dispaly_vector.push_back("if");
                _if->run(pc, instruction_memory);
                id->run_state = true;
            }
            dispaly_vector.push_back("-");
            clock++;
            std::cout << std::endl;
        }
    }
};