#include "dictionary.hh"

void Dict::insert(std::string w) {
    Trie *t = trie.add(&trie, indexMap.size() + 1, w.c_str());
    if (t) {
        //if (w == "alice")  std::cout << w << std::endl;
        indexMap.insert(std::pair<unsigned, Trie *>(cnt++, t));
    }
}

std::string Dict::find(unsigned index) {
    auto it = indexMap.find(index - 1);
    if (it != indexMap.end()) {
        return trie.find(it->second);
    }
    return "No element with this index.";
}

unsigned Dict::getIndex(std::string w) {
    return trie.findIndex(&trie, w.c_str());
}

void Dict::nMostFreq() {
}
