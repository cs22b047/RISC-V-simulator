#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <string>
#include <cmath>
// using namespace std;
class Core
{
public:
    long int regs[32];
    long int pc;
    std::ifstream program_file;
    std::string instruction;

public:
    Core()
    {
        for (int i = 0; i < 32; i++)
        {
            regs[i] = 0;
        }
        pc = 0;
    }
    bool execute(char *tail, std::unordered_map<std::string, char *> label_map)
    {
        // assign instruction string to the line pc is pointing to
        program_file.seekg(0);
        for (int i = 0; i <= pc; i++)
        {
            if (program_file.eof())
                return false;

            getline(program_file, instruction);
        }
        // std::cout << instruction << std::endl;
        // splitting instruction
        std::vector<std::string> parts;
        std::string part;
        std::istringstream iss(instruction);
        while (iss >> part)
        {
            parts.push_back(part);
        }
        if (parts.size() == 0)
        {
            pc++;
            return true;
        }
        auto it = parts.begin();
        execute_any(tail, it, parts, label_map);

        return true;
    }
    void execute_any(char *tail, std::vector<std::string>::iterator it, std::vector<std::string> parts, std::unordered_map<std::string, char *> label_map)
    {
        if (*it == ".text")
            pc++;
        if (*it == "addi")
            execute_addi(it);
        if (*it == "add")
            execute_add(it);
        if (*it == "sub")
            execute_sub(it);
        if (*it == "lw")
            execute_lw(it, label_map);
        if (*it == "sw")
            execute_sw(it);
        if (*it == "jal")
            execute_jal(it);
        if (*it == "bne")
            execute_bne(it);
        if (*it == "beq")
            execute_beq(it);
        if (*it == "bgt")
            execute_bgt(it);
        if (*it == "blt")
            execute_blt(it);
        if ((*it)[(*it).length() - 1] == ':')
            execute_label(it, parts, label_map, tail);
        if (*it == "la")
            execute_la(it, label_map);
        if (*it == "li")
            execute_li(it);
        if (*it == "j")
            execute_j(it);
        if(*it=="slli")
            execute_slli(it);
        if (*it == "ecall")
            execute_ecall();
    }
    // execute functions
    void execute_addi(std::vector<std::string>::iterator it)
    {
        int x1 = get_reg(++it);
        int x2 = get_reg(++it);
        it++;
        long int x3 = 0;

        for (int i = 0; i < (*it).length(); i++)
        {
            x3 = x3 * 10 + ((*it)[i] - 48);
        }
        regs[x1] = regs[x2] + x3;
        pc++;
    }
    void execute_add(std::vector<std::string>::iterator it)
    {
        int x1 = get_reg(++it);
        int x2 = get_reg(++it);
        int x3 = get_reg(++it);
        regs[x1] = regs[x2] + regs[x3];
        pc++;
    }
    void execute_sub(std::vector<std::string>::iterator it)
    {
        int x1 = get_reg(++it);
        int x2 = get_reg(++it);
        int x3 = get_reg(++it);
        regs[x1] = regs[x2] - regs[x3];
        pc++;
    }
    void execute_lw(std::vector<std::string>::iterator it, std::unordered_map<std::string, char *> label_map)
    {
        int x1 = get_reg(++it);
        it++;
        if ((*it)[(*it).length() - 1] == ')')
        {
            long int offset = 0;
            int i = 0;
            while ((*it)[i] != '(')
            {
                offset = offset * 10 + ((*it)[i] - 48);
                i++;
            }
            i += 2;
            int x2 = 0;
            while ((*it)[i] != ')')
            {
                x2 = x2 * 10 + ((*it)[i] - 48);
                i++;
            }
            regs[x1] = *(int *)(offset + regs[x2]);
            pc++;
        }
        else
        {

            regs[x1] = *(int *)label_map[(*it) + ":"];
            pc++;
        }
    }
    void execute_sw(std::vector<std::string>::iterator it)
    {
        int x1 = get_reg(++it);
        it++;
        if ((*it)[(*it).length() - 1] == ')')
        {
            long int offset = 0;
            int i = 0;
            while ((*it)[i] != '(')
            {
                offset = offset * 10 + ((*it)[i] - 48);
                i++;
            }
            i += 2;
            int x2 = 0;
            while ((*it)[i] != ')')
            {
                x2 = x2 * 10 + ((*it)[i] - 48);
                i++;
            }
            *(int *)(offset + regs[x2]) = regs[x1];
            pc++;
        }
    }
    void execute_jal(std::vector<std::string>::iterator it)
    {
        std::cout << "exe_addi";
    }
    void execute_j(std::vector<std::string>::iterator it)
    {
        it++;
        search_label(*it);
    }
    void execute_bne(std::vector<std::string>::iterator it)
    {
        int x1 = get_reg(++it);
        int x2 = get_reg(++it);
        if (regs[x1] != regs[x2])
        {
            it++;
            search_label(*it);
        }
        else
            pc++;
        std::cout << x1 << " " << x2;
    }
    void execute_beq(std::vector<std::string>::iterator it)
    {
        int x1 = get_reg(++it);
        int x2 = get_reg(++it);
        if (regs[x1] == regs[x2])
        {
            it++;
            search_label(*it);
        }
        else
            pc++;
    }
    void execute_bgt(std::vector<std::string>::iterator it)
    {
        int x1 = get_reg(++it);
        int x2 = get_reg(++it);
        if (regs[x1]>regs[x2])
        {
            it++;
            search_label(*it);
        }
        else
            pc++;
    }
    void execute_blt(std::vector<std::string>::iterator it)
    {
        int x1 = get_reg(++it);
        int x2 = get_reg(++it);
        if (regs[x1]<regs[x2])
        {
            it++;
            search_label(*it);
        }
        else
            pc++;
    }
    void execute_slli(std::vector<std::string>::iterator it)
    {
        int x1 = get_reg(++it);
        int x2 = get_reg(++it);
        regs[x1] = regs[x2]*std::pow(2,stoi(*(++it)));

        pc++;
    }
    void execute_la(std::vector<std::string>::iterator it, std::unordered_map<std::string, char *> label_map)
    {
        int x1 = get_reg(++it);
        regs[x1] = (long int)label_map[*(++it) + ":"];
        pc++;
    }
    void execute_li(std::vector<std::string>::iterator it)
    {
        int x1 = get_reg(++it);
        it++;
        regs[x1] = stoi(*it);
        pc++;
    }
    void execute_label(std::vector<std::string>::iterator it, std::vector<std::string> parts, std::unordered_map<std::string, char *> label_map, char *tail)
    {
        if (parts.size() == 1)
        {
            pc++;
            return;
        }
        it++;
        execute_any(tail, it, parts, label_map);
    }
    void execute_ecall()
    {
        switch (regs[17])
        {
        case 1:
            std::cout << regs[10];
            break;
        case 4:
            char *c = (char *)regs[10];
            while (*c != '\0')
            {
                std::cout << *c;
                c++;
            }
            std::cout<<std::endl;
            break;
        }
        pc++;
    }
    // util functions
    int get_reg(std::vector<std::string>::iterator it)
    {
        int reg_id = 0;
        for (int i = 1; i < (*it).length(); i++)
        {
            reg_id = reg_id * 10 + ((*it)[i] - 48);
        }
        return reg_id;
    }
    bool search_label(std::string label)
    {
        program_file.seekg(0);
        std::string temp;
        int i = 0;
        while (getline(program_file, temp))
        {
            std::string part;
            std::istringstream iss(temp);
            iss >> part;
            if (part == (label + ":"))
            {
                pc = i;
                return true;
            }
            i++;
        }
        return false;
    }
    void printReg()
    {
        for (int i = 0; i < 32; i++)
        {
            std::cout << "x" << (i) << ":    " << regs[i] << std::endl;
        }
    }
};
class Processor
{
public:
    char *memory;
    char *tail;

    std::unordered_map<std::string, char *> label_map;
    int clock = 0;
    Core *cores[2] = {new Core(), new Core()};
    Processor()
    {
        memory = (char *)malloc(4000 * sizeof(char));
        tail = memory;
        if (memory == NULL)
            std::cout << "memory not allocated";
        else
            std::cout << "memory allocated at:" << memory << std::endl;
    }
    void run()
    {
        while (cores[0]->execute(memory, label_map))
        {
        }
        cores[0]->printReg();
        cores[1]->printReg();
    }
    void parse(Core *core);
    void allocate_memory();
    void print_memory();
    std::string trim(const std::string &s);
};
void Processor::parse(Core *core)
{
    std::string temp;
    while (getline(core->program_file, temp))
    {
        core->pc++;
        temp = trim(temp);

        if (temp == ".data")
        {
            while (getline(core->program_file, temp))
            {
                core->pc++;
                temp = trim(temp);
                if (temp == ".text")
                    return;
                std::string part;
                std::istringstream iss(temp);
                iss >> part;
                label_map[part] = tail;
                iss >> part;
                if (part == ".word")
                {
                    while (iss >> part)
                    {
                        int n = stoi(part);
                        *(int *)tail = n;
                        tail = tail + sizeof(int);
                    }
                }
                if (part == ".string")
                {
                    iss >> part;
                    for (int i = 0; i < part.length(); i++)
                    {
                        if (part[i] == '"')
                            continue;
                        *tail = part[i];
                        tail += sizeof(char);
                    }
                    while (iss >> part)
                    {
                        *tail = ' ';
                        tail += sizeof(char);
                        for (int i = 0; i < part.length(); i++)
                        {
                            if (part[i] == '"')
                                continue;
                            *tail = part[i];
                            tail += sizeof(char);
                        }
                    }
                    *tail = '\0';
                    tail += sizeof(char);
                }
            }
        }
    }
}
void Processor::print_memory()
{
    char *ptr = memory;
    //   std::cout<<ptr[0]<<"abc"<<*(ptr+1);
    while (ptr!=tail)
    {
        std::cout << *(int*)ptr<<" ";
        ptr += sizeof(int);
    }
}
void Processor::allocate_memory()
{
}

std::string Processor::trim(const std::string &s)
{
    auto start = s.begin();
    while (start != s.end() && std::isspace(*start))
    {
        start++;
    }

    auto end = s.end();
    do
    {
        end--;
    } while (std::distance(start, end) > 0 && std::isspace(*end));

    return std::string(start, end + 1);
}
int main()
{
    Processor *sim = new Processor();

    sim->cores[0]->program_file.open("/home/tilak/Projects/Risc-v_sim/program3.txt");
    sim->cores[1]->program_file.open("/home/tilak/Projects/Risc-v_sim/program2.txt");
    sim->parse(sim->cores[0]);
        sim->print_memory();

    sim->run();
        sim->print_memory();
    return 0;
}
