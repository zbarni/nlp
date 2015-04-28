#include <iostream>
#include <unordered_map>
#include "trie.hh"
typedef std::unordered_map<unsigned, Trie *> IndexMap;

class Dict {
    public:
        Dict() : cnt(0) {}
        ~Dict() {}

        void        insert(std::string w);
        std::string find(unsigned ind);
        unsigned    getIndex(std::string w);
        void        nMostFreq();
        
    private:
        Trie trie;
        IndexMap indexMap;
        unsigned long cnt;
};
