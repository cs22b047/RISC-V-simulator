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

    int L2_cacheSize; //total number of bytes
    int L2_blockSize; //number of bytes per block
    int L2_associativity; //number of blocks per set
    int L2_numSets;
    //vector of list to keep track of oreder of block accesses
    //each list corresponds to a set in cache
    std::vector<std::list<uint32_t>> dq;
    //vectro of unordered map, each map represents a set in cache
    std::vector<std::unordered_map<uint32_t , std::list<uint32_t >::iterator>> cache;
    std::vector<std::list<uint32_t>> l2dq;

    std::vector<std::unordered_map<uint32_t , std::list<uint32_t >::iterator>> l2cache;

    bool l1miss=false;
    

public:
    Cache(int cacheSize, int blockSize, int associativity,int L2_cacheSize,int L2_blockSize,int L2_associativity)
    {
        this->blockSize = blockSize;
        this->cacheSize = cacheSize;
        this->associativity = associativity;
        this->numSets = (cacheSize) / (blockSize * associativity);
        cache.resize(numSets);
        dq.resize(numSets);


        this->L2_blockSize = L2_blockSize;
        this->L2_cacheSize = L2_cacheSize;
        this->L2_associativity = L2_associativity;
        this->L2_numSets = (L2_cacheSize) / (L2_blockSize * L2_associativity);
        l2cache.resize(L2_numSets);
        l2dq.resize(L2_numSets);
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
            l1miss=true;
            //if set if full delete least resently used tag
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
            //if preset delete form list
            dq[index].erase(cache[index][tag]);
        }
        //add the tag to front of list(becomes MRU)
        dq[index].push_front(tag);
        //also insert tag and it's corresponding list iterator in map 
        cache[index][tag] = dq[index].begin();
        return hit;
    }

    bool L2_LRU(uint32_t address,bool instruction_MM)
    {
        bool hit;
        uint32_t tag;
        auto a = split(address,instruction_MM);
        uint32_t index = a.first;
        tag = a.second;
        //if tag is not present
        if (l2cache[index].find(tag) == l2cache[index].end())
        {
            hit = false;
            l1miss=true;
            //if set if full delete least resently used tag
            if (l2dq[index].size() == associativity)
            {
                uint32_t last = l2dq[index].back();
                l2dq.pop_back();
                l2cache[index].erase(last);
            }
        }
        else
        {
            hit = true;
            //if preset delete form list
            l2dq[index].erase(l2cache[index][tag]);
        }
        //add the tag to front of list(becomes MRU)
        l2dq[index].push_front(tag);
        //also insert tag and it's corresponding list iterator in map 
        l2cache[index][tag] = l2dq[index].begin();
        return hit;
    }
    //same as LRU except when set is full tag that is most recently used is removed
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
            l1miss=true;
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
        // for(auto it = cache.begin();it!=cache.end();it++){
        //     for(auto it2 = (*it).begin();it2 != (*it).end();it2++){
        //         // std::cout<<it2->first<<"   ";
        //     }
        //     // std::cout<<"--------------"<<std::endl;
        // }
    }
};