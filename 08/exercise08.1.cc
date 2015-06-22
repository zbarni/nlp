#include <iostream>
#include <fstream>
#include <string>
#include <math.h>       /* pow, abs */
#include <ctime>        /* time() */
#include "simple_lm_3gram.hh"

#define vocabLength         29
#define sentenceEndToken    1
#define unkToken            0

using namespace std;

/*
 * Works on new test data
 */
string getRandomSequence(string &line, double lambda)
{
    string randomisedLine;

    for (unsigned i = 0; i < line.length(); i = i + 1)
    {
        if((line[i] >= 'a' && line[i] <= 'z') || line[i] == ' ')    //just ignore numbers and punktuations marks
        {
            double lambdaCheckNr = (double)(rand() % 100)/100;
            if(lambdaCheckNr < lambda)
            {
                randomisedLine = randomisedLine + line[i];
            } else
            {
                char randomChar = (rand() % 25) + (int)'a';
                if(randomChar == line[i])
                {
                    randomChar = ' ';
                }
                randomisedLine = randomisedLine + randomChar;
            }
        }
    }

    return randomisedLine;
}

/*
 * Works on new test data
 */
double getLineAccuracy(string &line1, string &line2)
{
    if(abs((int)line1.length() - (int)line2.length()) == 0)
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
    return accuracy / line1.length();
}

/*
 * Works on new test data
 */
double getPLambdaXnCn(char x, char c, double lambda)
{
    if(x == c)
    {
        return lambda;
    } else
    {
        if(((x >= 'a' && x <= 'z') || x == ' ') && ((c >= 'a' && c <= 'z') || c == ' '))
        {
            return lambda;                              // we have a <unk> and numbers or punktuations mark combinantion
        } else
        {
            return (1 - lambda)/25;                     //X is 26(a..z & _)
        }
    }
}

/*
 * Works on new test data
 */
string getMinimumStringErrorRateSpellingCorrection(string &line, double lambda)
{
    unsigned short bestCurrentChar      = 2;
    unsigned short prevousChar          = 2;                            //sentence beginn token
    unsigned short prePrevousChar       = 2;                            //sentence beginn token
    unsigned short prePrePrevousChar    = 2;                            //sentence beginn token
    double probability;
    double maxProbability;

    string correctedLine;
    for(unsigned i = 0; i < line.length(); i = i + 2)
    {
        maxProbability = 0;
        for(unsigned j = 0; j <= vocabLength; j++)
        {
            if(j == 1)
            {
                j = 3;                                                  //just skip the sentence symbols
            }
            if(j == 3)                                                  // since vocab[3] == '_' use space ' ' instead
            {
                probability = getPLambdaXnCn(' ',         line[i], lambda) * pow(exp(1.0), scores[j][prePrevousChar][prevousChar]);
                //probability = getPLambdaXnCn(' ',         line[i], lambda) * pow(exp(1.0), scores[j][prePrePrevousChar][prePrevousChar][prevousChar]);
            }else
            {
                probability = getPLambdaXnCn(vocab[j][0], line[i], lambda) * pow(exp(1.0), scores[j][prePrevousChar][prevousChar]);
                //probability = getPLambdaXnCn(vocab[j][0], line[i], lambda) * pow(exp(1.0), scores[j][prePrePrevousChar][prePrevousChar][prevousChar]);
            }
            if (probability > maxProbability)
            {
                maxProbability = probability;
                bestCurrentChar = j;                                    // save arg max
            }
        }
        if(bestCurrentChar == unkToken)
        {
            correctedLine = correctedLine + line[i];                    //remain symbol
        } else
        {
            correctedLine = correctedLine + vocab[bestCurrentChar];     // rebuild the "corrected" sentence
        }
        prevousChar         = bestCurrentChar;
        prePrevousChar      = prevousChar;
        prePrePrevousChar   = prePrevousChar;
    }

    return correctedLine;
}

/*
 * Works on new test data
 */
void partA(double lambda){
    string line;
    string lineRandom;
    string lineCorrected;
    double xErrorAccuracy       = 0;
    double cErrorAccuracy       = 0;
    unsigned int documentLength = 0;
    ifstream myFile ("e-test.ref");

    if (myFile.is_open())
    {
        while(getline (myFile,line))
        {
            lineRandom = getRandomSequence(line, lambda);
            lineCorrected = getMinimumStringErrorRateSpellingCorrection(lineRandom, lambda);
            xErrorAccuracy += getLineAccuracy(line, lineRandom) * line.length();                // = # of correct characters
            cErrorAccuracy += getLineAccuracy(line, lineCorrected) * line.length();             // = # of correct characters
            documentLength += line.length();
        }
        xErrorAccuracy /= documentLength;                                                       // = document's accuracy (instead of line's accuracy)
        cErrorAccuracy /= documentLength;                                                       // = document's accuracy (instead of line's accuracy)
        cout << "Lambda: " << lambda << " with error rate improvment: " << - cErrorAccuracy + xErrorAccuracy << endl;
        cout << "The error rates are: X error rate" << 1 - xErrorAccuracy << ", C error rate" << 1 - cErrorAccuracy << endl;
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

    cout << "1.a)" << endl;
    double lambda;
    for(unsigned i = 1; i < 10; i++)
    {
        lambda = (double)i/10;
        partA(lambda);
    }
    return 0;
}
