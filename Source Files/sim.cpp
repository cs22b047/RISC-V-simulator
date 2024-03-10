#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <bitset>
#include <../Header Files/Processor.h>

// utility functions
std::string trim(const std::string &s)
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
int get_reg(std::vector<std::string>::iterator it)
{
    int reg_id = 0;
    for (int i = 1; i < (*it).length(); i++)
    {
        reg_id = reg_id * 10 + ((*it)[i] - 48);
    }
    return reg_id;
}
void print_memory(std::vector<std::bitset<32>> &instruction_memory)
{
    std::cout << "printmemory" << std::endl;
    auto it = instruction_memory.begin();
    for (it; it < instruction_memory.end(); it++)
    {
        std::cout << *it << std::endl;
    }
}
void print_labels(std::unordered_map<std::string, long int> &label_map)
{
    for (auto &it : label_map)
    {
        std::cout << it.first << " " << it.second << std::endl;
    }
}

void parse_data(std::string instruction, char *&tail, std::unordered_map<std::string, long int> &label_map, char *&memory)
{
    std::string part;
    std::istringstream iss(instruction);
    iss >> part;
    label_map[part] = (long int)(tail - memory);
    iss >> part;
    if (part == ".word")
    {
        while (iss >> part)
        {
            if (part[0] == '#')
                break;
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
void parse_text(std::string instruction, std::vector<std::bitset<32>> &instruction_memory, std::unordered_map<std::string, long int> &label_map, char *memory)
{
    std::vector<std::string> parts;
    std::string part;
    std::istringstream iss(instruction);
    while (iss >> part)
    {
        parts.push_back(part);
    }
    std::bitset<7> func7;
    std::bitset<5> rs2;
    std::bitset<5> rs1;
    std::bitset<3> funct3;
    std::bitset<5> rd;
    std::bitset<7> oppcode;
    std::bitset<32> final;
    std::bitset<12> immediate;
    auto it = parts.begin();
    if (*it == "add")
    {
        int x1 = get_reg(++it);
        int x2 = get_reg(++it);
        int x3 = get_reg(++it);
        func7 = 0;
        rs1 = x2;
        rs2 = x3;
        rd = x1;
        funct3 = 0;
        oppcode = 51;
        for (int i = 0; i < 7; i++)
        {
            final[i] = oppcode[i];
        }
        for (int i = 7; i < 12; i++)
        {
            final[i] = rd[i - 7];
        }
        for (int i = 12; i < 15; i++)
        {
            final[i] = funct3[i - 12];
        }
        for (int i = 15; i < 20; i++)
        {
            final[i] = rs1[i - 15];
        }
        for (int i = 20; i < 25; i++)
        {
            final[i] = rs2[i - 20];
        }
        for (int i = 25; i < 32; i++)
        {
            final[i] = func7[i - 25];
        }
        instruction_memory.push_back(final);
    }
    if (*it == "sub")
    {
        int x1 = get_reg(++it);
        int x2 = get_reg(++it);
        int x3 = get_reg(++it);
        func7 = 32;
        rs1 = x2;
        rs2 = x3;
        rd = x1;
        funct3 = 0;
        oppcode = 52;
        for (int i = 0; i < 7; i++)
        {
            final[i] = oppcode[i];
        }
        for (int i = 7; i < 12; i++)
        {
            final[i] = rd[i - 7];
        }
        for (int i = 12; i < 15; i++)
        {
            final[i] = funct3[i - 12];
        }
        for (int i = 15; i < 20; i++)
        {
            final[i] = rs1[i - 15];
        }
        for (int i = 20; i < 25; i++)
        {
            final[i] = rs2[i - 20];
        }
        for (int i = 25; i < 32; i++)
        {
            final[i] = func7[i - 25];
        }
        instruction_memory.push_back(final);
    }
    if (*it == "addi")
    {
        int x1 = get_reg(++it);
        int x2 = get_reg(++it);
        ++it;
        int x3 = stoi(*it);
        immediate = x3;
        std::cout << immediate << std::endl;
        rs1 = x2;
        rd = x1;
        funct3 = 0;
        oppcode = 50;
        for (int i = 0; i < 7; i++)
        {
            final[i] = oppcode[i];
        }
        for (int i = 7; i < 12; i++)
        {
            final[i] = rd[i - 7];
        }
        for (int i = 12; i < 15; i++)
        {
            final[i] = funct3[i - 12];
        }
        for (int i = 15; i < 20; i++)
        {
            final[i] = rs1[i - 15];
        }
        for (int i = 20; i < 32; i++)
        {
            final[i] = immediate[i - 20];
        }
        instruction_memory.push_back(final);
    }
    if (*it == "lw")
    {
        oppcode = 53;
        rd = get_reg(++it);
        it++;
        if (!isdigit((*it)[0]))
        {
            immediate = label_map[(*it) + ":"];
            std::cout << immediate << std::endl;
            rs1 = 0;
        }
        else
        {
            int x2 = 0;
            int offset = 0;
            int i = 0;
            while ((*it)[i] != '(')
            {
                int p = (*it)[i] - '0';
                offset *= 10;
                offset += p;
                i++;
            }
            i += 2;
            while ((*it)[i] != ')')
            {
                int p = (*it)[i] - '0';
                x2 *= 10;
                x2 += p;
                i++;
            }
            immediate = offset;
            rs1 = x2;
        }
        funct3 = 0;
        for (int i = 0; i < 7; i++)
        {
            final[i] = oppcode[i];
        }
        for (int i = 7; i < 12; i++)
        {
            final[i] = rd[i - 7];
        }
        for (int i = 12; i < 15; i++)
        {
            final[i] = funct3[i - 12];
        }
        for (int i = 15; i < 20; i++)
        {
            final[i] = rs1[i - 15];
        }
        for (int i = 20; i < 32; i++)
        {
            final[i] = immediate[i - 20];
        }
        std::cout << immediate << std::endl;

        instruction_memory.push_back(final);
    }
    if (*it == "sw")
    {
        oppcode = 54;
        int x1 = get_reg(++it);
        it++;
        int x2 = 0;
        int offset = 0;
        int i = 0;
        while ((*it)[i] != '(')
        {
            int p = (*it)[i] - '0';
            offset *= 10;
            offset += p;
            i++;
        }
        i += 2;
        while ((*it)[i] != ')')
        {
            int p = (*it)[i] - '0';
            x2 *= 10;
            x2 += p;
            i++;
        }
        immediate = offset;
        rs1 = x1;
        rd = x2;
        funct3 = 0;
        for (int i = 0; i < 7; i++)
        {
            final[i] = oppcode[i];
        }
        for (int i = 7; i < 12; i++)
        {
            final[i] = rd[i - 7];
        }
        for (int i = 12; i < 15; i++)
        {
            final[i] = funct3[i - 12];
        }
        for (int i = 15; i < 20; i++)
        {
            final[i] = rs1[i - 15];
        }
        for (int i = 20; i < 32; i++)
        {
            final[i] = immediate[i - 20];
        }
        instruction_memory.push_back(final);
    }
    if (*it == "bne")
    {
        rs2 = get_reg(++it);
        rs1 = get_reg(++it);
        it++;
        immediate = label_map[(*it) + ":"];
        oppcode = 55;
        funct3 = 0;
        for (int i = 0; i < 7; i++)
        {
            final[i] = oppcode[i];
        }
        for (int i = 7; i < 12; i++)
        {
            final[i] = immediate[i - 7];
        }
        for (int i = 12; i < 15; i++)
        {
            final[i] = funct3[i - 12];
        }
        for (int i = 15; i < 20; i++)
        {
            final[i] = rs1[i - 15];
        }
        for (int i = 20; i < 25; i++)
        {
            final[i] = rs2[i - 20];
        }
        for (int i = 25; i < 32; i++)
        {
            final[i] = immediate[i - 20];
        }
        instruction_memory.push_back(final);
    }
    if (*it == "beq")
    {
        rs2 = get_reg(++it);
        rs1 = get_reg(++it);
        it++;
        immediate = label_map[(*it) + ":"];
        oppcode = 56;
        funct3 = 0;
        for (int i = 0; i < 7; i++)
        {
            final[i] = oppcode[i];
        }
        for (int i = 7; i < 12; i++)
        {
            final[i] = immediate[i - 7];
        }
        for (int i = 12; i < 15; i++)
        {
            final[i] = funct3[i - 12];
        }
        for (int i = 15; i < 20; i++)
        {
            final[i] = rs1[i - 15];
        }
        for (int i = 20; i < 25; i++)
        {
            final[i] = rs2[i - 20];
        }
        for (int i = 25; i < 32; i++)
        {
            final[i] = immediate[i - 20];
        }
        instruction_memory.push_back(final);
    }
    if (*it == "bgt")
    {
        rs2 = get_reg(++it);
        rs1 = get_reg(++it);
        it++;
        immediate = label_map[(*it) + ":"];
        oppcode = 57;
        funct3 = 0;
        for (int i = 0; i < 7; i++)
        {
            final[i] = oppcode[i];
        }
        for (int i = 7; i < 12; i++)
        {
            final[i] = immediate[i - 7];
        }
        for (int i = 12; i < 15; i++)
        {
            final[i] = funct3[i - 12];
        }
        for (int i = 15; i < 20; i++)
        {
            final[i] = rs1[i - 15];
        }
        for (int i = 20; i < 25; i++)
        {
            final[i] = rs2[i - 20];
        }
        for (int i = 25; i < 32; i++)
        {
            final[i] = immediate[i - 20];
        }
        instruction_memory.push_back(final);
    }
    if (*it == "blt")
    {
        rs2 = get_reg(++it);
        rs1 = get_reg(++it);
        it++;
        immediate = label_map[(*it) + ":"];
        oppcode = 58;
        funct3 = 0;
        for (int i = 0; i < 7; i++)
        {
            final[i] = oppcode[i];
        }
        for (int i = 7; i < 12; i++)
        {
            final[i] = immediate[i - 7];
        }
        for (int i = 12; i < 15; i++)
        {
            final[i] = funct3[i - 12];
        }
        for (int i = 15; i < 20; i++)
        {
            final[i] = rs1[i - 15];
        }
        for (int i = 20; i < 25; i++)
        {
            final[i] = rs2[i - 20];
        }
        for (int i = 25; i < 32; i++)
        {
            final[i] = immediate[i - 20];
        }
        instruction_memory.push_back(final);
    }
    if (*it == "slli")
    {
        int x1 = get_reg(++it);
        int x2 = get_reg(++it);
        long int x3 = 0;
        for (int i = 0; i < (*it).length(); i++)
        {
            x3 = x3 * 10 + ((*it)[i] - 48);
        }
        immediate = x3;
        rs1 = x2;
        rd = x1;
        funct3 = 0;
        oppcode = 59;
        for (int i = 0; i < 7; i++)
        {
            final[i] = oppcode[i];
        }
        for (int i = 7; i < 12; i++)
        {
            final[i] = rd[i - 7];
        }
        for (int i = 12; i < 15; i++)
        {
            final[i] = funct3[i - 12];
        }
        for (int i = 15; i < 20; i++)
        {
            final[i] = rs1[i - 15];
        }
        for (int i = 20; i < 32; i++)
        {
            final[i] = immediate[i - 20];
        }
        instruction_memory.push_back(final);
    }
    if (*it == "li")
    {
        rd = get_reg(++it);
        it++;
        immediate = stoi(*it);
        oppcode = 60;
        funct3 = 0;
        rs1 = 0;
        for (int i = 0; i < 7; i++)
        {
            final[i] = oppcode[i];
        }
        for (int i = 7; i < 12; i++)
        {
            final[i] = rd[i - 7];
        }
        for (int i = 12; i < 15; i++)
        {
            final[i] = funct3[i - 12];
        }
        for (int i = 15; i < 20; i++)
        {
            final[i] = rs1[i - 15];
        }
        for (int i = 20; i < 32; i++)
        {
            final[i] = immediate[i - 20];
        }
        instruction_memory.push_back(final);
    }
    if (*it == "la")
    {
        rd = get_reg(++it);
        it++;
        immediate = label_map[(*it) + ":"];
        oppcode = 61;
        funct3 = 0;
        rs1 = 0;
        for (int i = 0; i < 7; i++)
        {
            final[i] = oppcode[i];
        }
        for (int i = 7; i < 12; i++)
        {
            final[i] = rd[i - 7];
        }
        for (int i = 12; i < 15; i++)
        {
            final[i] = funct3[i - 12];
        }
        for (int i = 15; i < 20; i++)
        {
            final[i] = rs1[i - 15];
        }
        for (int i = 20; i < 32; i++)
        {
            final[i] = immediate[i - 20];
        }
        instruction_memory.push_back(final);
    }
    if (*it == "j")
    {
        it++;
        immediate = label_map[(*it) + ":"];
        oppcode = 62;
        funct3 = 0;
        rd = 0;
        rs1 = 0;
        for (int i = 0; i < 7; i++)
        {
            final[i] = oppcode[i];
        }
        for (int i = 7; i < 12; i++)
        {
            final[i] = rd[i - 7];
        }
        for (int i = 12; i < 15; i++)
        {
            final[i] = funct3[i - 12];
        }
        for (int i = 15; i < 20; i++)
        {
            final[i] = rs1[i - 15];
        }
        for (int i = 20; i < 32; i++)
        {
            final[i] = immediate[i - 20];
        }
        instruction_memory.push_back(final);
    }
    if (*it == "ecall")
    {
        it++;
        immediate = 0;
        oppcode = 69;
        funct3 = 0;
        rd = 0;
        rs1 = 0;
        for (int i = 0; i < 7; i++)
        {
            final[i] = oppcode[i];
        }
        for (int i = 7; i < 12; i++)
        {
            final[i] = rd[i - 7];
        }
        for (int i = 12; i < 15; i++)
        {
            final[i] = funct3[i - 12];
        }
        for (int i = 15; i < 20; i++)
        {
            final[i] = rs1[i - 15];
        }
        for (int i = 20; i < 32; i++)
        {
            final[i] = immediate[i - 20];
        }
        instruction_memory.push_back(final);
    }
}
int main()
{
    Processor *sim = new Processor();
    std::ifstream program_file1;
    std::ifstream program_file2;
    program_file1.open("/home/tilak/Projects/Risc-v_sim/Test files/program1.txt");
    program_file2.open("/home/tilak/Projects/Risc-v_sim/Test files/program3.txt");
    std::string instruction;
    bool data_section = false;
    bool text_section = true;
    int index = 0;
    
    // label parsing
    while (getline(program_file1, instruction))
    {
        instruction = trim(instruction);
        if (instruction == "")
            continue;
        if (instruction == ".data")
        {
            data_section = true;
            text_section = false;
            continue;
        }
        if (instruction == ".text")
        {
            text_section = true;
            data_section = false;
            continue;
        }
        if (text_section)
        {
            // std::cout << "label parse" << instruction << std::endl;
            std::string part;
            std::istringstream iss(instruction);
            iss >> part;

            if (part[part.length() - 1] == ':')
            {
                std::string temp;
                if (iss >> temp)
                {
                    sim->label_map1[part] = index;
                }
                else
                {
                    sim->label_map1[part] = index;
                    index--;
                }
            }

            index++;
        }
    }
    // data and text parsing
    program_file1.clear();
    program_file1.seekg(0, program_file1.beg);
    while (getline(program_file1, instruction))
    {
        instruction = trim(instruction);
        if (instruction == "")
            continue;
        if (instruction == ".data")
        {
            data_section = true;
            text_section = false;
            continue;
        }
        if (instruction == ".text")
        {
            text_section = true;
            data_section = false;
            continue;
        }
        if (data_section)
            parse_data(instruction, sim->tail1, sim->label_map1, sim->memory1);
        if (text_section)
        {
            parse_text(instruction, sim->instruction_memory1, sim->label_map1, sim->memory1);
        }
    }


    while (getline(program_file2, instruction))
    {
        instruction = trim(instruction);
        if (instruction == "")
            continue;
        if (instruction == ".data")
        {
            data_section = true;
            text_section = false;
            continue;
        }
        if (instruction == ".text")
        {
            text_section = true;
            data_section = false;
            continue;
        }
        if (text_section)
        {
            // std::cout << "label parse" << instruction << std::endl;
            std::string part;
            std::istringstream iss(instruction);
            iss >> part;

            if (part[part.length() - 1] == ':')
            {
                std::string temp;
                if (iss >> temp)
                {
                    sim->label_map2[part] = index;
                }
                else
                {
                    sim->label_map2[part] = index;
                    index--;
                }
            }

            index++;
        }
    }
    // data and text parsing
    program_file2.clear();
    program_file2.seekg(0, program_file2.beg);
    while (getline(program_file2, instruction))
    {
        instruction = trim(instruction);
        if (instruction == "")
            continue;
        if (instruction == ".data")
        {
            data_section = true;
            text_section = false;
            continue;
        }
        if (instruction == ".text")
        {
            text_section = true;
            data_section = false;
            continue;
        }
        if (data_section)
            parse_data(instruction, sim->tail2, sim->label_map2,sim->memory2);
        if (text_section)
        {
            parse_text(instruction, sim->instruction_memory2, sim->label_map2, sim->memory2);
        }
    }
    print_memory(sim->instruction_memory1);
    print_labels(sim->label_map1);
    std::string s;
    std::cout<<"Ecexecute core 1 with data forwarding(y/n): ";
    std::cin>>s;
    if(s=="y"){
        sim->forward1=true;
    }else sim->forward1=false;
    std::cout<<"Ecexecute core 2 with data forwarding(y/n): ";
    std::cin>>s;
    if(s=="y"){
        sim->forward2=true;
    }else sim->forward2=false;
    sim->run();
    sim->print_regs();
}