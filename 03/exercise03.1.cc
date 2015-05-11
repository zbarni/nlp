// FIXME We assume that the training / test data are sorted according 
// to class names

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include "dictionary.hh"
#include "newsgroup.hh"
#define VOCABULARY  "20news/20news.voc"
#define TRAINING    "20news/20news.tr"
#define TEST        "20news/20news.te"
using namespace std;
int N;

void readLine(string &line, Dict *dict) {
    string word;
    bool newWord;
    bool firstWord = true;
    char c;
    newWord = true;
    for (unsigned j = 0; j < line.length(); j++)
    {
        c = tolower(line[j]);
        if(c != ' ')
        {
            if(newWord)
            {
                if(!firstWord)
                {
                    dict->insert(word);
                }
                else
                {
                    firstWord = false;
                }
                word = c;
                newWord = false;
            }
            else
            {
                word += c;
            }
        }
        else
        {
            newWord = true;
        }
    }
    dict->insert(word);
}

void readVocabulary(const string &file, Dict &voc) {
    ifstream myfile (file);
    string line;
    int cnt = 0;
    if (myfile.is_open()) {
        while(getline (myfile,line) && (cnt++ < N || N == -1))  {
            readLine(line, &voc);
        }
        myfile.close();
    }
    else {
        cout << "Unable to open vocabulary file";
    }
}

string getNextWord(const string &line, unsigned &pos) {
    string word = "";
    char c;
    unsigned j;
    for (j = pos; (j < line.length()) && (line[j] != ' '); j++) {
        c = tolower(line[j]);
        word += c;
    }
    pos = j+1;
    return word;
}

double readTraining(const string &file, map<string, NewsGroup *> &newsgroups,
        Dict &vocabulary) {
    ifstream myfile (file);
    string line;
    string word;
    string class_n;
    unsigned pos;
    unsigned nr;
    double sum_classes = 0;
    NewsGroup *ng;

    if (myfile.is_open()) {
        while(getline (myfile,line)) {
            pos     = 0;
            getNextWord(line, pos); // doc name, discard
            class_n = getNextWord(line, pos); // class name
            auto c_it = newsgroups.find(class_n); // search for class
            if (c_it == newsgroups.end()) {
                ng = new NewsGroup(word);
                ng->occur = 1;
                newsgroups.insert(pair<string, NewsGroup *>(word, ng));
            }
            else {
                ng = c_it->second;
                ng->occur ++;
            }
            sum_classes ++;
            while (pos < line.length()) {
                word = getNextWord(line, pos);
                // check if we should ignore or not
                if (vocabulary.find(word)) {
                    nr = stoi(getNextWord(line, pos));
                    ng->dict.insert(nr, word);
                    ng->doclength += nr;
                }
            }
        }
        myfile.close();
    }
    else {
        cout << "Unable to open vocabulary file";
    }
    return sum_classes;
}

void processTrainingData(double sum_classes, 
        map<string, NewsGroup *> &newsgroups) {

    for (auto c_it : newsgroups) {
        NewsGroup *ng = c_it.second;
        // update priors for each newsgroup / class
        ng->prior = ng->occur / sum_classes;
        
        // calculate lambda
        ng->lambda = ng->doclength / (double)(ng->occur);
//        cout << c_it.first << " " << ng->lambda << endl;
    }
}

double wordLikelihood(std::string w, NewsGroup *ng) {
    return ng->dict.getFrequency(w) / (double)(ng->doclength);
}

double poisson(int N, double lambda) {
    
}

void processTestData(map<string, NewsGroup *> &newsgroups) {
    int     pos;
    string  line;
    string  word;
    string  ref_class;
    NewsGroup *ng;
    ifstream test_file(TEST);

    if (test_file.is_open()) {
        while(getline (test_file,line)) {
            ng = new NewsGroup("TestGroup");
            getNextWord(line, pos); // doc name, discard
            pos = 0;
            // class name, just for error measurement
            ref_class = getNextWord(line, pos); 

            // read test document and fill dictionary
            while (pos < line.length()) {
                word = getNextWord(line, pos);
                nr   = stoi(getNextWord(line, pos));
                ng->dict.insert(nr, word);
                ng->doclength += nr;
            }

            // check which newsgroup it belongs to
            for (auto it : newsgroups) {
                NewsGroup *c = it.second;
                double p = 0;
                p += c->prior;
                p *= poisson(ng->doclength, c->lambda); // ~Poisson of p(N|c)
            }

            delete(ng);
        }
    }
    else {
        cout << "Error while opening test file" << endl;
    }
}

int main (int argc, char *argv[]) {
    double sum_classes;
    string line;
    string param;
    Dict voc;
    map<string, NewsGroup *> newsgroups;

    if(argc > 1) {
        param = argv[1];
        N = stoi(param);
    }
    else {
        N = -1;
    }

    // read vocabulary
    readVocabulary(VOCABULARY, voc);
    sum_classes = readTraining(TRAINING, newsgroups, voc);
    processTrainingData(sum_classes, newsgroups);
    processTestData(newsgroups);
//    cout << wordLikelihood("subject", newsgroups["alt.atheism"]) << endl;
//    cout << newsgroups["alt.atheism"]->dict.getFrequency("subject") << endl;
    return 0;
}
