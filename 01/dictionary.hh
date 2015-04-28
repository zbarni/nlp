#include<iostream>
#include "trie.hh"

class Dict {
    public:
        Dict() {}
        ~Dict() {}

        void        insert(std::string w);
        std::string findByIndex(unsigned ind);
        unsigned    getIndex(std::string w);
        void        nMostFreq();
        
    private:
        Trie trie;
        std::vector<Trie *> indexMap;
        unsigned long cnt;
};
