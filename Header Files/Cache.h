#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <list>
// struct uint32_t / {
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
    uint32_t tag;
    std::list<uint32_t > dq;
    std::vector<std::unordered_map<uint32_t , std::list<uint32_t >::iterator>> cache;

public:
    Cache(int cacheSize, int blockSize, int associativity)
    {
        this->blockSize = blockSize;
        this->cacheSize = cacheSize;
        this->associativity = associativity;
        this->numSets = (cacheSize) / (blockSize * associativity);
        cache.resize(numSets);
    }
    std::pair<uint32_t, uint32_t> split(uint32_t address)
    {
        int offset = log2(blockSize);
        address = address >> offset;
        uint32_t index = address & ((1 << numSets) - 1);
        uint32_t tag = address >> (int)log2(numSets);
        return {index, tag};
    }
    bool LRU(uint32_t address)
    {
        bool hit;
        uint32_t tag;
        auto a = split(address);
        uint32_t index = a.first;
        tag = a.second;
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
};