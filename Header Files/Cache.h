#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <list>
// struct cacheBlock {
//     uint32_t tag;   
//     bool vaild = false;
// };
class Cache
{
private:
    int cacheSize;
    int blockSize;
    int associativity;
    int numSets;
    std::list<uint32_t > dq;
    std::vector<std::unordered_map<uint32_t , std::list<uint32_t >::iterator>> cache;

public:
    Cache(int cacheSize, int blockSize, int associativity)
    {
        this->blockSize = blockSize;
        this->cacheSize = cacheSize;
        this->associativity = associativity;
        this->numSets = (cacheSize) / (blockSize * associativity);
        // std::cout<<"num sets: "<<numSets<<std::endl;
        cache.resize(numSets);
    }
    std::pair<uint32_t, uint32_t> split(uint32_t address,bool instruction_MM)
    {
        int offset = log2(blockSize);
        address = address >> offset;
        uint32_t index = address%numSets;
        uint32_t tag = address >> (int)log2(numSets);
        if(instruction_MM){
            tag = tag | (1<<31);
        }
        return {index, tag};
    }
    bool LRU(uint32_t address,bool instruction_MM)
    {
        bool hit;
        uint32_t tag;
        // std::cout<<"lru add: "<<address;
        auto a = split(address,instruction_MM);
        uint32_t index = a.first;
        tag = a.second;
        // std::cout<<"index: "<<index<<std::endl;
        // std::cout<<"tag: "<<tag<<std::endl;
        if (cache[index].find(tag) == cache[index].end())
        {
            hit = false;
            if (dq.size() == associativity)
            {
                uint32_t last = dq.back();
                dq.pop_back();
                cache[index].erase(last);
            }
        }
        else
        {
            hit = true;
            dq.erase(cache[index][tag]);
        }
        dq.push_front(tag);
        cache[index][tag] = dq.begin();
        return hit;
    }
    bool MRU(uint32_t address,bool instruction_MM)
    {
        bool hit;
        uint32_t tag;
        // std::cout<<"lru add: "<<address;
        auto a = split(address,instruction_MM);
        uint32_t index = a.first;
        tag = a.second;
        // std::cout<<"index: "<<index<<std::endl;
        // std::cout<<"tag: "<<tag<<std::endl;
        if (cache[index].find(tag) == cache[index].end())
        {
            hit = false;
            if (dq.size() == associativity)
            {
                uint32_t first = dq.front();
                dq.pop_front();
                cache[index].erase(first);
            }
        }
        else
        {
            hit = true;
            dq.erase(cache[index][tag]);
        }
        dq.push_back(tag);
        cache[index][tag] = dq.end();
        return hit;
    }
    void pirnt_cashe(){
        for(auto it = cache.begin();it!=cache.end();it++){
            for(auto it2 = (*it).begin();it2 != (*it).end();it2++){
                // std::cout<<it2->first<<"   ";
            }
            // std::cout<<"--------------"<<std::endl;
        }
    }
};