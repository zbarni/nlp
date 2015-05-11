#include "trie.hh"

Trie::Trie():
    pred(0),
    first_indx(-1),
    occur(0),
    son(0)
{
    std::memset(next,0,sizeof(next));
    punctuation['?'] = OFFSET + 1;
    punctuation['!'] = OFFSET + 2;
    punctuation['['] = OFFSET + 3;
    punctuation[']'] = OFFSET + 4;
    punctuation['('] = OFFSET + 5;
    punctuation[')'] = OFFSET + 6;
    punctuation['\''] = OFFSET + 7;
    punctuation['-'] = OFFSET + 8; 
    punctuation[','] = OFFSET + 9; 
    punctuation['.'] = OFFSET + 10; 
    punctuation[';'] = OFFSET + 11; 
    punctuation[':'] = OFFSET + 12; 
    punctuation['*'] = OFFSET + 13; 
    punctuation['_'] = OFFSET + 14; 
    punctuation['`'] = OFFSET + 15; 
    punctuation['"'] = OFFSET + 16; 
} 

int Trie::getPos(const char *w) {
    if (*w >= 'a' && *w <='z') {
        return *w-'a'; 
    }
    else if (*w <= '9' && *w >= '0') {
        return OFFSET_NR + (*w - '0') + 1;
    }
    else return punctuation[*w];
}

/*
    Returns a pointer to the leave if insertion was successful,
    and 0 otherwise (word already in the trie).
*/
Trie* Trie::add(Trie *t, int nr, const char *w) {
    if (*w=='\0') {
        if (t->occur) {
            t->occur += nr;
            return 0;
        }
        t->occur += nr;
        return t;
    }
    int pos;
    pos = getPos(w);
    if (!t->next[pos]) {
        ++t->son;
        t->next[pos] = new Trie;
        t->next[pos]->pred = t;
        t->next[pos]->c = *w;
    }
    return add(t->next[pos], nr, w+1);
}

std::string Trie::find(Trie *t) {
    if (!t->pred) {
        return std::string();
    }
    return (find(t->pred)) + t->c;
}

unsigned Trie::getFrequency(Trie *t, const char *w) {
    if (!t) {
        return 0; 
    }
    return (*w=='\0') ? t->occur : getFrequency(t->next[getPos(w)], w+1);
}

int Trie::del(Trie *T,Trie *t, const char *w)
{
    int pos = getPos(w);
    if (*w == '\0')
        --t->occur;
    else if (del(T,t->next[pos],w+1)) {
        t->next[pos]=0;
        --t->son;
    }
    if (!t->son && !t->occur && t!=T) {
        delete t;
        return 1;
    }
    return 0;
}

//int app (trie *t,char *w)
//{
//    if (*w=='\0')
//        return t->occur;
//    int pos=*w-'a';
//    if (t->next[pos])
//        return app(t->next[pos],w+1);
//    return 0;
//}
//
//int pref (trie *t,char *w,int k)
//{
//    if (*w=='\0')
//        return k;
//    int pos=*w-'a';
//    if (!t->next[pos])
//        return k;
//    return pref(t->next[pos],w+1,k+1);
//}

