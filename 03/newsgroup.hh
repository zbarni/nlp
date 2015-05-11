#ifndef NEWSGROUP_H
#define NEWSGROUP_H
#include "dictionary.hh"

class NewsGroup {
    public:
        NewsGroup(std::string _name) : name(_name),
                occur(0),
                doclength(0),
                prior(0.0),
                lambda(0)
                {} 
        ~NewsGroup();

        std::string name;
        unsigned    occur;
        unsigned    doclength; // total number of words in newsgroup 
        double      prior;  // class prior probability
        double      lambda; // for poisson distribution of length
        Dict        dict;   // dictionary containing all the words

};

#endif // NEWSGROUP_H
