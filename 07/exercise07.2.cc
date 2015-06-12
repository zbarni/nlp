// FIXME We assume that the training / test data are sorted according 
// to class names

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>       /* pow */
#include <ctime>
#include "simple_lm.hh"

#define vocabLength         29
#define sentenceEndToken    1

using namespace std;
int N;

double getSentencePerplexity(string &line)
{
    init_vocab();                               //from simple_lm
    init_lm();                                  //from simple_lm

    unsigned short currentChar = 2;
    unsigned short prevousChar = 2;             //sentence beginn token
    double perplexity = 0;

    for (unsigned i = 0; i < line.length(); i = i + 2)
    {
        prevousChar = currentChar;
        for (unsigned j = vocabLength; j > 0; j--)
        {
            currentChar = j;
            if((char)line[i] == (char)vocab[j][0])
            {
                break;
            }
        }
        perplexity = perplexity + pow(10 ,scores[prevousChar][currentChar]);
    }
    perplexity = perplexity + pow(10 ,scores[currentChar][sentenceEndToken]);
    perplexity = pow(perplexity, -(2/((double)line.length())+1));
    return perplexity;
}

void partA()
{
    string line;
    double perplexity;
    double lowestPerplexity = 1;
    double highestPerplexity = 0;
    unsigned int posLowestPerplexity = 0;
    unsigned int posHighestPerplexity = 0;
    unsigned int i = 0;


    ifstream myFile ("test_data");
    if (myFile.is_open())
    {
        while(getline (myFile,line))
        {
            i++;
            perplexity = getSentencePerplexity(line);
            if(perplexity < lowestPerplexity)
            {
                lowestPerplexity = perplexity;
                posLowestPerplexity = i;
            }
            if(perplexity > highestPerplexity)
            {
                highestPerplexity = perplexity;
                posHighestPerplexity = i;
            }
        }
    } else
    {
        cout << "error opening test_data" << endl;
    }
    cout << "Highest Perplexity: " << highestPerplexity << " of Sentence: " << posHighestPerplexity << endl;
    cout << "Lowest Perplexity: " << lowestPerplexity << " of Sentence: " << posLowestPerplexity << endl;
}

string getRandomSequence(string &line, double lambda)
{
    srand (time(NULL));
    double lambdaRandomCheck;
    cout << (int)'a' << endl;
    return line;
}

void partB(){
    string line;
    string lineRandom;
    lineRandom = getRandomSequence(line, 1);
}

int main (int argc, char *argv[])
{
    //partA();
    partB();
    return 0;
}
