#ifndef TRIE_H
#define TRIE_H

#include<map>
#include<vector>
#include<cstdio>
#include<cstring>
#include<string>
#define TRIE_SIZE 26 + 10 + 16
#define OFFSET 35
#define OFFSET_NR 25 

// Trie data structure
class Trie {
    public:
        Trie();
        ~Trie() {}

        Trie*   add(Trie *t, int ind, const char *c);
        std::string find(Trie *t);
        unsigned getFrequency(Trie *t, const char *w);
        int     del(Trie *T,Trie *t,const char *w);
        int     getPos(const char *w);
    private:

        Trie *next[TRIE_SIZE];
        Trie *pred;
        char c;
        int first_indx;
        int occur;
        int son;
        std::map<char, int> punctuation;
};
#endif // TRIE_H
