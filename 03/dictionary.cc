#include "dictionary.hh"

void Dict::insert(std::string w) {
    Trie *t = trie.add(&trie, indexMap.size() + 1, w.c_str());
    if (t) {
        indexMap.insert(std::pair<unsigned, Trie *>(cnt++, t));
    }
}

void Dict::insert(unsigned nr, std::string w) {
    Trie *t = trie.add(&trie, nr, w.c_str());
    if (t) {
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

bool Dict::find(const std::string &w) {
//    return trie.find(&trie, w) != 0;
    return getFrequency(w) > 0;
}

unsigned Dict::getFrequency(std::string w) {
    return trie.getFrequency(&trie, w.c_str());
}

void Dict::nMostFreq() {
}
