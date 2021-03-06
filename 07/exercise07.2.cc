// FIXME We assume that the training / test data are sorted according
// to class names

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>       /* pow, abs */
#include <ctime>        /* time() */
#include "simple_lm.hh"

#define vocabLength         29
#define sentenceEndToken    1

using namespace std;

/*
 * a)
 */
double getSentencePerplexity(string &line)
{
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
        perplexity = perplexity + pow(exp(1.0) ,scores[currentChar][prevousChar]);
    }
    perplexity = perplexity + pow(exp(1.0) ,scores[sentenceEndToken][currentChar]);
    perplexity = pow(perplexity, -(2/((double)line.length())+1));
    return perplexity;
}

void partA()
{
    string line;
    double perplexity;
    double lowestPerplexity           = 1;
    double highestPerplexity          = 0;
    unsigned int posLowestPerplexity  = 0;
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
    cout << "Lowest Perplexity: "  << lowestPerplexity  << " of Sentence: " << posLowestPerplexity << endl << endl;
}

/*
 * b)
 */
string getRandomSequence(string &line, double lambda)
{
    string randomisedLine;

    for (unsigned i = 0; i < line.length(); i = i + 2)
    {
        double lambdaCheckNr = (double)(rand() % 100)/100;
        if(lambdaCheckNr < lambda)
        {
            randomisedLine = randomisedLine + line[i] + " ";
        } else
        {
            char randomChar = (rand() % 25) + (int)'a';
            if(randomChar == line[i])
            {
                randomChar = '_';
            }
            randomisedLine = randomisedLine + randomChar + " ";
        }
    }

    return randomisedLine;
}

/*
 * c)
 */
double getLineAccuracy(string &line1, string &line2)
{
    if(abs((int)line1.length() - (int)line2.length()) > 1)
    {
        return -1;                      //check if both lines are of equal lengh
    }
    double accuracy = 0;
    for (unsigned i = 0; i < line1.length(); i = i + 2)
    {
        if(line1[i] == line2[i])
        {
            accuracy++;
        }
    }
    return accuracy / ((int)min(line1.length() + 1, line2.length() + 1)/2);
}

double getPLambdaXnCn(char x, char c, double lambda)
{
    if(x == c)
    {
        return lambda;
    } else
    {
        return (1 - lambda)/25;         //X is 26(a..z & _)
    }
}

/*
 * d)
 */
string getMinimumStringErrorRateSpellingCorrection(string &line, double lambda)
{
    unsigned short bestCurrentChar = 2;
    unsigned short prevousChar = 2;                                     //sentence beginn token
    double probability;
    double maxProbability;

    string correctedLine;
    for(unsigned i = 0; i < line.length(); i = i + 2)
    {
        maxProbability = 0;
        for(unsigned j = 3; j <= vocabLength; j++)                      // 3 - vocamLength because 0 .. 2 are <unk> and sentence beginn/end
        {                                                               // what we will all not need here
            probability = getPLambdaXnCn(vocab[j][0], line[i], lambda) * pow(exp(1.0), scores[j][prevousChar]);
            if (probability > maxProbability)
            {
                maxProbability = probability;
                bestCurrentChar = j;                                    // save arg max
            }
        }
        correctedLine = correctedLine + vocab[bestCurrentChar] + " ";   // rebuild the "corrected" sentence
        prevousChar   = bestCurrentChar;
    }

    return correctedLine;
}

void partD(double lambda){
    string line;
    string lineRandom;
    string lineCorrected;
    double xErrorAccuracy       = 0;
    double cErrorAccuracy       = 0;
    unsigned int documentLength = 0;
    ifstream myFile ("test_data");

    if (myFile.is_open())
    {
        while(getline (myFile,line))
        {
            lineRandom = getRandomSequence(line, lambda);
            lineCorrected = getMinimumStringErrorRateSpellingCorrection(lineRandom, lambda);
            xErrorAccuracy += getLineAccuracy(line, lineRandom) * (line.length() + 1) / 2;      // = # of correct characters
            cErrorAccuracy += getLineAccuracy(line, lineCorrected) * (line.length() + 1) / 2;   // = # of correct characters
            documentLength += (line.length() + 1) / 2;                                          // = document length
        }
        xErrorAccuracy /= documentLength;                                                       // = document's accuracy (instead of line's accuracy)
        cErrorAccuracy /= documentLength;                                                       // = document's accuracy (instead of line's accuracy)
        cout << "Lambda: " << lambda << " with accuracy improvment: " << cErrorAccuracy - xErrorAccuracy << endl;
        cout << "The error rates are: X accuracy " << xErrorAccuracy << ", C accuracy " << cErrorAccuracy << endl;
    } else
    {
        cout << "error opening test_data" << endl;
    }
}

int main (int argc, char *argv[])
{
    srand (time(NULL));
    init_vocab();                               //from simple_lm
    init_lm();                                  //from simple_lm

    cout << "2.a)" << endl;
    partA();

    cout << "2.d)" << endl;
    double lambda;
    for(unsigned i = 1; i < 10; i++)
    {
        lambda = (double)i/10;
        partD(lambda);
    }
    return 0;
}
