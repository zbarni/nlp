#include "dictionary.hh"

//Dict::Dict() : 
//    {}
    
void Dict::insert(std::string w) {
    Trie *t = trie.add(&trie, indexMap.size() + 1, w.c_str());
    if (t) {
        //if (w == "alice")  std::cout << w << std::endl;
        indexMap.push_back(t);
    }
}

std::string Dict::findByIndex(unsigned index) {
    return trie.find(indexMap[index - 1]);
}

unsigned Dict::getIndex(std::string w) {
    return trie.findIndex(&trie, w.c_str());
}

void Dict::nMostFreq() {
}
