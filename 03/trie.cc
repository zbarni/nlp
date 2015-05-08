#include "trie.hh"

Trie::Trie():
    pred(0),
    first_indx(-1),
    inf(0),
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
Trie* Trie::add(Trie *t, int ind, const char *w) {
    if (*w=='\0') {
        if (t->inf) return 0;
        ++t->inf;
        t->first_indx = ind;
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
    return add(t->next[pos], ind, w+1);
}

std::string Trie::find(Trie *t) {
    if (!t->pred) {
        return std::string();
    }
    return (find(t->pred)) + t->c;
}

int Trie::findIndex(Trie *t, const char *w) {
    if (*w=='\0') {
        return t->first_indx;
    }
    int pos;
    pos = getPos(w);
    return findIndex(t->next[pos], w+1);
}

int Trie::del(Trie *T,Trie *t, const char *w)
{
    int pos = getPos(w);
    if (*w == '\0')
        --t->inf;
    else if (del(T,t->next[pos],w+1)) {
        t->next[pos]=0;
        --t->son;
    }
    if (!t->son && !t->inf && t!=T) {
        delete t;
        return 1;
    }
    return 0;
}

//int app (trie *t,char *w)
//{
//    if (*w=='\0')
//        return t->inf;
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

