#include "../Header Files/Processor.h"

void Processor::parse(Core *core,std::unordered_map<std::string, char *> &label_map,char* &tail)
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
// void Processor::print_memory()
// {
//     char *ptr = memory;
//     //   std::cout<<ptr[0]<<"abc"<<*(ptr+1);
//     while (ptr!=tail)
//     {
//         std::cout << *(int*)ptr<<" ";
//         ptr += sizeof(int);
//     }
// }
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