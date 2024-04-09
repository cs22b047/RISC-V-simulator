#include <iostream>
#include <string>
#include <vector>
#include <./IF.h>
#include <./ID.h>
#include <./EXE.h>
#include <./MEM.h>
#include <./WB.h>
#include <./Cache.h>
class Core
{
public:
    long int regs[33];
    int pc = 0;
    IF *_if = new IF();
    ID *id = new ID();
    EXE *exe = new EXE();
    MEM *mem = new MEM();
    WB *wb = new WB();
    Cache * cache = new Cache(2048,8,8);
    std::vector<std::string> dispaly_vector[200];
    int hits=0;
    int missess = 0;
    int instruction_count = 0;
    int clock = 0;
    int stalls = 0;
    int clock2 = 0;
    int clock3 = 0;
    bool datahazard = false;
    bool datahazard1 = false;
    bool miss = true;
    int offset = 0;
    Core()
    {
        for (int i = 0; i < 31; i++)
        {
            regs[i] = 0;
        }
    }
    bool detect(int rd, int rs1, int rs2)
    {
        return (rd == rs1) || (rd == rs2);
    }
    bool label = false;
    void run(std::vector<std::bitset<32>> &instruction_memory, char *&memory, bool forward)
    {
        auto it = instruction_memory.begin();
        for (it; it < instruction_memory.end(); it++)
        {
            std::cout << *it << std::endl;
        }
        while (!wb->eof)
        {
            std::cout << "cycle " << clock << "  ";
            datahazard = (detect(exe->rd, id->x1, id->x2) && (clock >= 2));
            datahazard1 = (detect(mem->rd, id->x1, id->x2) && (clock >= 3));
            // if(col)
            if (datahazard || datahazard1)
            {
                // std::cout << "data hazard" << std::endl;

                if (!forward)
                {
                    stalls++;
                    exe->stall = true;
                }

                else
                {
                    if (id->x1 == exe->rd)
                    {
                        regs[32] = exe->result;
                        id->x1 = 32;
                    }
                    if (id->x2 == exe->rd)
                    {
                        regs[32] = exe->result;
                        id->x2 = 32;
                    }
                    if (id->x1 == mem->rd)
                    {
                        regs[32] = exe->result;
                        id->x1 = 32;
                    }
                    if (id->x2 == mem->rd)
                    {
                        regs[32] = exe->result;
                        id->x2 = 32;
                    }
                }
            }
            if (!forward)
            {
                if ((detect(wb->rd, id->x1, id->x2) && id->oppcode != 50) || (wb->rd == id->x1 && id->oppcode == 50))
                {
                    // std::cout << "hazard over" << std::endl;
                    if (datahazard1 || datahazard)
                    {
                        stalls--;
                    }
                    exe->stall = false;
                }
            }
            // if ((id->oppcode == 53 && id->x1 == 0)||id->oppcode==61)
            // {
            //     // std::cout << "lw hazard"<<std::endl;
            //     stalls++;
            //     exe->stall = true;
            //     clock2++;
            // }
            // if (clock2 == 4)
            // {
            //     clock2 = 0;
            //     exe->stall = false;
            // }
            if (exe->branch_taken)
            {
                exe->run_state = false;
                id->run_state = false;
                pc = exe->immediate;
                exe->branch_taken = false;
                _if->eof = false;
                id->eof = false;
            }
            if (clock >= 4 && wb->run_state)
            {
                dispaly_vector[clock].push_back("WB");
                wb->run(mem->rd, mem->result, regs, mem->oppcode, mem->eof, memory);
                instruction_count++;
            }
            if (clock >= 3 && !mem->eof && !mem->stall && mem->run_state)
            {
                dispaly_vector[clock].push_back("MM");
                if (exe->oppcode == 53)
                {
                    int miss_penality=1;
                    uint32_t address = exe->result;
                    if(cache->LRU(address)){
                        miss_penality = 5;
                        hits++;
                    }else{
                        missess++;
                        miss_penality = 10;
                    }
                    for (int i = 0; i < miss_penality - 1; i++)
                    {

                        mem->run(exe->oppcode, exe->result, exe->rd, exe->eof, exe->stall, exe->immediate, memory);
                        std::cout << std::endl;
                        std::cout << "cycle " << clock << "  ";
                        clock++;
                    }
                    mem->run(exe->oppcode, exe->result, exe->rd, exe->eof, exe->stall, exe->immediate, memory);
                }
                else
                {
                    mem->run(exe->oppcode, exe->result, exe->rd, exe->eof, exe->stall, exe->immediate, memory);
                }
                wb->run_state = true;
            }

            if (clock >= 2 && !exe->eof && !exe->stall && exe->run_state)
            {
                dispaly_vector[clock].push_back("EX");
                exe->run(id->oppcode, id->x1, id->x2, id->immediate, regs, id->rd, id->eof, (datahazard1 || datahazard));
                mem->stall = false;
                mem->run_state = true;
            }
            if (clock >= 1 && !(id->eof) && !exe->stall && id->run_state)
            {
                dispaly_vector[clock].push_back("ID");
                id->run(_if->instruction, regs, _if->eof);
                exe->run_state = true;
            }
            if (!_if->eof && !exe->stall)
            {
                for (int i = 0; i < offset; i++)
                {
                    dispaly_vector[clock].push_back("  ");
                }
                offset += stalls + 1;
                dispaly_vector[clock].push_back("IF");
                _if->run(pc, instruction_memory);
                id->run_state = true;
            }
            clock++;

            std::cout << std::endl;
        }
    }
};