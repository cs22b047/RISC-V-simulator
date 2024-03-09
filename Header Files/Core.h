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

    int clock = 0;

    int clock2 = 0;
    int clock3 = 0;
    bool datahazard = false;
    bool datahazard1 = false;
    bool detect(int rd, int rs1, int rs2)
    {
        return (rd == rs1) || (rd == rs2);
    }
    void run(std::vector<std::bitset<32>> &instruction_memory)
    {
        auto it = instruction_memory.begin();
        for (it; it < instruction_memory.end(); it++)
        {
            std::cout << *it << std::endl;
        }
        while (!wb->eof)
        {
            if (clock2 == 2)
            {
                datahazard = false;
                clock2 = 0;
            }

            if (clock > 4)
                wb->run(mem->rd, mem->result, regs, mem->oppcode, mem->eof);
            if (clock > 3)
                mem->run(exe->oppcode, exe->result, exe->rd, exe->eof);
            if (datahazard)
            {
                clock2++;
                clock++;
                std::cout << "stall" << std::endl;
                continue;
            }
            if (clock > 2)
                exe->run(id->oppcode, id->x1, id->x2, id->immediate, regs, id->rd, id->eof);
            if (clock > 1)
                id->run(_if->instruction, regs, _if->eof);

            _if->run(pc, instruction_memory);

            if (exe->rd != id->rd)
                datahazard = detect(exe->rd, id->x1, id->x2);

            clock++;
        }
    }
};