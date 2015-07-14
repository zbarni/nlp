#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <climits>
#include <map>
#include <cmath>
#include <vector>
#include <limits>
#include <cassert>

#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))
#define Nmax 40
#define Imax 30
using namespace std;

double lambda;
unsigned nrSourceWords;
unsigned nrTargetWords;
double Q[Nmax][Nmax][Nmax];
int decisionDelta[Nmax][Nmax][Nmax]; // store the delta leading to the best decision 
int decisionWord[Nmax][Nmax][Nmax]; // store the e' leading to the best decision 
double trans[Nmax][Nmax]; // p(i | i - delta) --> [i][delta]
map <string, int> eVocabulary;
map <int, string> eIndToWord;
map <string, int> fVocabulary;
double lexicon[Nmax][Nmax]; // <fIndex, pair<eIndex, probability>>
double bigramLM[Nmax][Nmax];

/*
 * basically numberOfWordsInSentence returns the number of spaces + 1
 */
unsigned numberOfWordsInSentence(string &sentence)
{
    if(sentence.length() == 0)
        return 0;

    unsigned number = 1;
    unsigned positionOfSpace = sentence.find(" ");
    while( positionOfSpace != UINT_MAX)
    {
        number++;
        positionOfSpace = sentence.find(" ", positionOfSpace + 1);
    }

    return number;
}

/*
 * Implementation of the Levenshtein distance for words
 */
int numberOfWordErrorsInSentence(string &sentence1, string &sentence2)
{
    int numberOfSentence1Words = numberOfWordsInSentence(sentence1);
    int numberOfSentence2Words = numberOfWordsInSentence(sentence2);
    int levensteinMatrix[numberOfSentence1Words + 1][numberOfSentence2Words + 1];

    //initialisation
    for(int i = 0; i <= numberOfSentence1Words; i++)
    {
        levensteinMatrix[i][0] = i;
    }
    for(int i = 0; i <= numberOfSentence2Words; i++)
    {
        levensteinMatrix[0][i] = i;
    }

    //work
    size_t prevousPositionSentence1   = 0;
    size_t positionOfSpaceInSentence1 = sentence1.find(" ");
    size_t prevousPositionSentence2   = 0;
    size_t positionOfSpaceInSentence2 = sentence2.find(" ");
    string word1, word2;
    for(int i = 1; i <= numberOfSentence1Words; i++)
    {
        //get one word
        //substr(position, length)
        word1 = sentence1.substr(prevousPositionSentence1, positionOfSpaceInSentence1 - prevousPositionSentence1);
        prevousPositionSentence1   = positionOfSpaceInSentence1 + 1;
        positionOfSpaceInSentence1 = sentence1.find(" ", positionOfSpaceInSentence1 + 1);
        for(int j = 1; j <= numberOfSentence2Words; j++)
        {
            //get one word
            word2 = sentence2.substr(prevousPositionSentence2, positionOfSpaceInSentence2 - prevousPositionSentence2);
            prevousPositionSentence2   = positionOfSpaceInSentence2 + 1;
            positionOfSpaceInSentence2 = sentence2.find(" " , positionOfSpaceInSentence2 + 1);

            levensteinMatrix[i][j] = MIN3(levensteinMatrix[i - 1][j] + 1,   //deletion
                    levensteinMatrix[i][j - 1] + 1,   //insertion
                    levensteinMatrix[i - 1][j - 1] + (word1.compare(word2) == 0 ? 0 : 1));
            //case sensitive depending on equation of words);
        }
        // reset word list in sentence2
        prevousPositionSentence2   = 0;
        positionOfSpaceInSentence2 = sentence2.find(" ");
    }

    return levensteinMatrix[numberOfSentence1Words][numberOfSentence2Words];
}

/*
 *
 */
double getWER(string &hypothesisSentence, string &referenceSentence)
{
    if(referenceSentence.length() == 0)
    {
        if(hypothesisSentence.length() == 0)
        {
            return 0;
        } else
        {
            //everything is wrong
            return 1;   //I assume it is one since the error rate is given in percent
        }
    } else
    {
        if(hypothesisSentence.length() == 0)
        {
            //everything is wrong
            return 1;   //I assume it is one since the error rate is given in percent
        }
    }

    double numberOfErrors         = numberOfWordErrorsInSentence(hypothesisSentence, referenceSentence);
    double numberOfReferenceWords = numberOfWordsInSentence(referenceSentence);

    return min((double)numberOfErrors/numberOfReferenceWords, (double)1);
}


/*
 *
 */
double getPER(string &hypothesisSentence, string &referenceSentence)
{
    if(referenceSentence.length() == 0)
    {
        if(hypothesisSentence.length() == 0)
        {
            return 0;
        } else
        {
            //everything is wrong
            return 1;   //I assume it is one since the error rate is given in percent
        }
    } else
    {
        if(hypothesisSentence.length() == 0)
        {
            //everything is wrong
            return 1;   //I assume it is one since the error rate is given in percent
        }
    }

    unsigned numberOfHypothesisWords = numberOfWordsInSentence(hypothesisSentence);
    double numberOfReferenceWords    = numberOfWordsInSentence(referenceSentence);
    int numberOfDeletions            = 0;
    int numberOfInsertions           = 0;
    string word;

    // to get no infixes, we add to every word the spaces around it in search,
    // here we add it for the first and last word in both sentences
    hypothesisSentence = " " + hypothesisSentence + " ";
    referenceSentence  = " " + referenceSentence  + " ";

    size_t prevousPositionSentence   = 1;                                   // = 1 to get no out_of_range excepion
    size_t positionOfSpaceInSentence = hypothesisSentence.find(" ", 1);     // , 1 to spare the first space

    // number of deletions in hypothesisSentence
    for(unsigned i = 0; i < numberOfHypothesisWords; i++)
    {
        //hint: the -1 and +1 in this substr is to get the spaces in the word so we will not get counts on infixes
        word = hypothesisSentence.substr(prevousPositionSentence - 1, positionOfSpaceInSentence - prevousPositionSentence + 1);
        prevousPositionSentence   = positionOfSpaceInSentence + 1;
        positionOfSpaceInSentence = hypothesisSentence.find(" ", positionOfSpaceInSentence + 1);
        if(referenceSentence.find(word) == string::npos)
        {
            numberOfDeletions++;
        }
    }

    prevousPositionSentence   = 1;
    positionOfSpaceInSentence = referenceSentence.find(" ", 1);
    // number of insertions in hypothesisSentence
    for(unsigned i = 0; i < numberOfReferenceWords; i++)
    {
        word = referenceSentence.substr(prevousPositionSentence - 1, positionOfSpaceInSentence - prevousPositionSentence + 1);
        prevousPositionSentence   = positionOfSpaceInSentence + 1;
        positionOfSpaceInSentence = referenceSentence.find(" ", positionOfSpaceInSentence + 1);
        if(hypothesisSentence.find(word) == string::npos)
        {
            numberOfInsertions++;
        }
    }

    //if we have more insertions than deletions every deletion can be replaced by a substitution and vice versa
    double numberOfErrors = max(numberOfInsertions, numberOfDeletions);
    return min(numberOfErrors/numberOfReferenceWords, (double)1);
}

/*
 * calculation of the Lambda as defined in lecture
 */
double getLengthModelLambda()
{
    ifstream e_file("feldmann/e");
    ifstream f_file("feldmann/f");

    string lineE;
    string lineF;

    double sumOfWordsE = 0;
    double sumOfWordsF = 0;

    while(getline(e_file,lineE) && getline(f_file, lineF))
    {
        sumOfWordsE += numberOfWordsInSentence(lineE);
        sumOfWordsF += numberOfWordsInSentence(lineF) - 1; //since every sentence in f is ending with a space
    }

    e_file.close();
    f_file.close();

    return sumOfWordsF/sumOfWordsE;
}

unsigned factorial(unsigned number)
{
    unsigned fac = 1;
    while(number > 0)
    {
        fac = fac * number;
        number--;
    }
    return fac;
}

double getLengthProbability(double I, unsigned J)
{
    return exp(-lambda*I)*pow(lambda*I,J)/factorial(J);
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

void initVocabulary() 
{
    string line;
    int cnt = 0;
    // open LM file
    ifstream targetLMFile("feldmann/lm-e");
    if (!targetLMFile.is_open()) 
    {
        cout << "Could not open target LM file. Exiting." << endl;
        exit(-1);
    }

    while(getline (targetLMFile,line)) 
        if (line.find("1-grams") != string::npos) 
        {
            while(getline (targetLMFile,line))
            {
                if (line == "") break;
                vector<string> tokens = split(line, '\t');
                eVocabulary[tokens[1]] = cnt++;
                eIndToWord[cnt - 1] = tokens[1];
            }
            break;
        }
    nrTargetWords = cnt;

    cnt = 0;
    ifstream sourceLMFile("feldmann/lm-f");
    if (!sourceLMFile.is_open()) 
    {
        cout << "Could not open source LM file. Exiting." << endl;
        exit(-1);
    }

    while(getline (sourceLMFile,line)) 
        if (line.find("1-grams") != string::npos) 
        {
            while(getline (sourceLMFile,line))
            {
                if (line == "") break;
                vector<string> tokens = split(line, '\t');
                fVocabulary[tokens[1]] = cnt++;
            }
            break;
        }
    nrSourceWords = cnt;
}

double logToProb(double l)
{
    return pow(10, l);
}

double probToLog(double p)
{
    return log10(p);
}

void parseLexicon()
{
    string line;
    ifstream file("feldmann/lexicon.probs");
    if (!file.is_open()) 
    {
        cout << "Could not open lexicon probability file. Exiting." << endl;
        exit(-1);
    }

    while(getline (file,line)) 
    {
        vector<string> tokens = split(line, ' ');
        if (!eVocabulary.count(tokens[1]) || !fVocabulary.count(tokens[0]))
        {
            cout << "Words in lexicon not present in language models files. Exiting." << endl;
            exit(-1);
        }
        double prob = stod(tokens[2]);
        lexicon[fVocabulary[tokens[0]]][eVocabulary[tokens[1]]] = prob;
    }
    /*for(unsigned i = 2; i < 40; i++)      //DEBUG ONLY
    {
        for(unsigned j = 2; j < 30; j++)
        {
            cout << "f: " << i << " e: " << j << " prob: "<< lexicon[i][j]<< endl;
        }
    }*/
}

void parseTransitions() 
{
    string line;
    int i, delta;
    ifstream file("feldmann/transition.probs");
    if (!file.is_open()) 
    {
        cout << "Could not open transition probability file. Exiting." << endl;
        exit(-1);
    }

    while(getline (file,line)) 
    {
        if (line == "") return;
        vector<string> tokens = split(line, ' ');
        delta = stoi(tokens[0]);
        i = stoi(tokens[1]);
        trans[delta][i] = probToLog(stod(tokens[2]));
    }
}

void parseTargetLM() 
{
    string line;
    string w1, w2;
    map<int, pair<double, double>> onegram;
    ifstream file("feldmann/lm-e");
    if (!file.is_open()) 
    {
        cout << "Could not open transition probability file. Exiting." << endl;
        exit(-1);
    }

    while(getline (file,line)) 
    {
        if (line.find("1-grams") != string::npos) 
        {
            while(getline (file,line)) 
            {
                if (line == "" || line == "\n") break;
                vector<string> tokens = split(line, '\t');
                double fallbackProb;
                if (tokens.size() < 3)
                    fallbackProb = -99;
                else
                    fallbackProb = stod(tokens[2]);
                onegram[eVocabulary[tokens[1]]] = make_pair(stod(tokens[0]), fallbackProb);
            }
            getline (file,line);
        }
        if (line.find("2-grams") != string::npos) 
        {
            while(getline (file,line)) 
            {
                if (line == "") break;
                vector<string> tokens = split(line, '\t');
                vector<string> words = split(tokens[1], ' ');
                bigramLM[eVocabulary[words[0]]][eVocabulary[words[1]]] = stod(tokens[0]);
            }
            break;
        }
    }

    for (unsigned i = 0; i < nrTargetWords; ++i)
    {
        for (unsigned j = 0; j < nrTargetWords; ++j)
        {
            if (!bigramLM[i][j]) 
            {
                bigramLM[i][j] = onegram[i].second + onegram[j].first;
            }
        }
    }
}

double deltaTrans(int delta, int e, int ePrimeInd)
{
    if (delta == 0)
    {
        return probToLog(e == ePrimeInd);
    }

    if (delta == 1)
    {
       return bigramLM[ePrimeInd][e]; 
    }
    //cout << "foo" << endl;

    double bestScore = -numeric_limits<double>::max();
    for (map<string,int>::iterator eIt = eVocabulary.begin(); eIt != eVocabulary.end(); ++eIt)
    {
        int eTilde = eVocabulary[eIt->first];
        double score = bigramLM[eTilde][e] + bigramLM[ePrimeInd][eTilde];
        if (score > bestScore)
        {
            bestScore = score;
        }
    }
    return bestScore;
}

double computeMax(int j, int i, int e, int &bestDelta, int &bestPrevWordInd)
{
    double bestScore = -numeric_limits<double>::max();
    double score;
    for (int delta = 0; delta < 3; ++delta)
    {
        for (map<string,int>::iterator eIt = eVocabulary.begin(); eIt != eVocabulary.end(); ++eIt)
        {
            int ePrimeInd = eVocabulary[eIt->first];
            score = trans[delta][max(i - delta, 1)] + deltaTrans(delta, e, ePrimeInd) + Q[ePrimeInd][i][j];

            if (score > bestScore)
            {
                bestScore = score;
                bestDelta = delta;
                bestPrevWordInd = ePrimeInd;
            }
        }
    }
    //cout << bestScore << endl;
    assert(-numeric_limits<double>::max() != bestScore);
    return bestScore;
}

void traceback(int i, int j, int eInd)
{
    if (i < 1 || j < 1)
    {
        return;
    }
    traceback(i - decisionDelta[eInd][i][j], j - 1, decisionWord[eInd][i][j]);
    cout << eIndToWord[eInd] << " ";
}

void DPSearch(double lambda)
{
    string line;
    string sentence;
    string word;
    initVocabulary();
    parseLexicon();
    parseTransitions();
    parseTargetLM();

    ifstream sourceTestFile("feldmann/f-test");
    if (!sourceTestFile.is_open()) 
    {
        cout << "Could not open source test file. Exiting." << endl;
        exit(-1);
    }

    // for each sentence in source file
    while(getline(sourceTestFile, sentence))
    {
        cout << "Sentence to be translated: " << endl << "\t" << sentence << endl;
        // for each word in sentence
        vector<string> tokens = split(sentence, ' ');
        for (unsigned j = 1; j <= tokens.size(); ++j)
        {
            word = tokens[j - 1];
            // for each position 1...Imax
            for (unsigned i = 1; i <= Imax; ++i) 
            {
                // for each word e'
                for (map<string,int>::iterator eIt = eVocabulary.begin(); eIt != eVocabulary.end(); ++eIt)
                {
                    int bestDelta = -1;
                    int bestPrevWordInd = -1;
                    double lexicalLogProbability = probToLog(lexicon[fVocabulary[word]][eVocabulary[eIt->first]]);
                    double maximalRecursion = computeMax(j, i, eVocabulary[eIt->first], bestDelta, bestPrevWordInd);
                    Q[eVocabulary[eIt->first]][i][j] = lexicalLogProbability + maximalRecursion;
                    decisionDelta[eVocabulary[eIt->first]][i][j] = bestDelta;
                    decisionWord[eVocabulary[eIt->first]][i][j] = bestPrevWordInd;
                    /*cout << "Q: " << Q[eVocabulary[eIt->first]][i][j];        //DEBUG ONLY
                    cout << " computeMax: "<< maximalRecursion;
                    cout << " lexicon: " << lexicalLogProbability;
                    cout << endl;*/
                }
            }
        }
        // traceback best solution
        int J = tokens.size();
        int bestI = -1;
        int bestPrevWordInd = -1;
        double bestScore = -numeric_limits<double>::max();
        for (unsigned I = 1; I < Imax; ++I)
        {
            // for each word e~ (tilde)
            for (map<string,int>::iterator eIt = eVocabulary.begin(); eIt != eVocabulary.end(); ++eIt)
            {
                double score = log10(getLengthProbability(I, J)) + Q[eVocabulary[eIt->first]][I][J];
//                cout << "logLengthProb: " << getLengthProbability(I, J) << ", lambda: " << lambda << ", Q[value]: " << Q[eVocabulary[eIt->first]][I][J] << endl;
                if (score > bestScore)
                {
                    bestScore = score;
                    bestI = I;
                    bestPrevWordInd = eVocabulary[eIt->first];
                }
            }        
        }
        cout << "Translation: " << endl << "\t";
        traceback(bestI, J, bestPrevWordInd);
        cout << endl;
        cout << "logarithmic bestScore: " << bestScore << "\nbestI: " << bestI << "\nbestEPrime(maximizing word): " << eIndToWord[bestPrevWordInd] << endl;
        cout << endl << endl;
    }
}

int main (int argc, char *argv[])
{
    lambda = getLengthModelLambda();
    DPSearch(lambda);
    string testShort = "dies bla ein test";
    string testLong  = "test dies blub ein blaaa";
//    double test = getPER(testShort, testLong);
//    cout << test << endl;
    return 0;
}
