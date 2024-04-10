#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <list>
class Cache
{
private:
    int cacheSize; //total number of bytes
    int blockSize; //number of bytes per block
    int associativity; //number of blocks per set
    int numSets;
    //list to keep track of oreder of block accesses
    std::vector<std::list<uint32_t>> dq;
    //vectro of unordered map, each map represents a set in cache
    std::vector<std::unordered_map<uint32_t , std::list<uint32_t >::iterator>> cache;

public:
    Cache(int cacheSize, int blockSize, int associativity)
    {
        this->blockSize = blockSize;
        this->cacheSize = cacheSize;
        this->associativity = associativity;
        this->numSets = (cacheSize) / (blockSize * associativity);
        cache.resize(numSets);
        dq.resize(numSets);
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
        auto a = split(address,instruction_MM);
        uint32_t index = a.first;
        tag = a.second;
        //if tag is not present
        if (cache[index].find(tag) == cache[index].end())
        {
            hit = false;
            if (dq[index].size() == associativity)
            {
                uint32_t last = dq[index].back();
                dq.pop_back();
                cache[index].erase(last);
            }
        }
        else
        {
            hit = true;
            dq[index].erase(cache[index][tag]);
        }
        dq[index].push_front(tag);
        cache[index][tag] = dq[index].begin();
        return hit;
    }
    bool MRU(uint32_t address,bool instruction_MM)
    {
        bool hit;
        uint32_t tag;
        auto a = split(address,instruction_MM);
        uint32_t index = a.first;
        tag = a.second;
        if (cache[index].find(tag) == cache[index].end())
        {
            hit = false;
            if (dq[index].size() == associativity)
            {
                uint32_t first = dq[index].front();
                dq[index].pop_front();
                cache[index].erase(first);
            }
        }
        else
        {
            hit = true;
            dq[index].erase(cache[index][tag]);
        }
        dq[index].push_back(tag);
        cache[index][tag] = dq[index].end();
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