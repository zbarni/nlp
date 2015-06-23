#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <cmath>       /* pow, abs */
#include <ctime>        /* time() */
#include "simple_lm.hh"

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
        if ((line[i] >= 'a' && line[i] <= 'z') || line[i] == ' ')    //just ignore numbers and punktuations marks
        {
            double lambdaCheckNr = (double)(rand() % 100)/100;
            if (lambdaCheckNr < lambda)
            {
                randomisedLine = randomisedLine + line[i];
            } 
            else
            {
                char randomChar = (rand() % 26) + (int)'a';  // 
                if (randomChar == line[i])
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
//    if((line1.length() != line2.length()))
//    {
//        return -1;                      //check if both lines are of equal lengh
//    }
    double accuracy = 0;
    for (unsigned i = 0; i < line1.length(); i = i + 1)
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
    } 
    else
    {
        if((isalpha(x) || x == ' ') && (isalpha(c) || c == ' '))
        {
            return (1 - lambda)/27;                     //X is 26(a..z & _)
        } 
        else
        {
            return lambda;                              // we have a <unk> and numbers or punktuations mark combinantion
        }
    }
}

/*
 Create a vector for ~Q_{n+1} by constructing it from N till the beginning (0).
*/
void initQtPost(const string line,  double lambda, vector< pair<string, double> > &Qt_n_post) 
{
    vector< pair<string, double> > Qt_nplus1_post;
    double sum;
    double res;
    // init last Q_{n+1} == N, with </s> as next char
    for (int k = 0; k < 30; ++k)
    {
        Qt_nplus1_post.push_back(make_pair(vocab[k],scores[k][1]));
    }

    // go backwards until i == 0 is reached
    for (int i = (int)line.size() - 1; i >= 0; --i)
    {
        Qt_n_post.clear();
        for (int c = 0; c < 30; ++c)
        {
            sum = 0;
            // iterate over every c' and sum p(c|c')
            for(unsigned cPrime = 0; cPrime <= vocabLength; cPrime++)
            {
                // sum as probability, convert later to log
                //TODO maybe swap the matrix indexes?
                sum += pow(exp(1.0), scores[cPrime][c] + Qt_nplus1_post[cPrime].second);
            }
            // use logs for comparison 
            res = log(getPLambdaXnCn(line[i], vocab[c][0], lambda)) + log(sum);
            Qt_n_post.push_back(make_pair(vocab[c], res));
        }
        Qt_nplus1_post = Qt_n_post;
    }
    // don't have to return anything cause values are contained in Qt_n_post
}

unsigned getCharIndex(char c) 
{
    for(unsigned j = 0; j <= vocabLength; j++) 
    {
        if (vocab[j][0] == c) 
            return j;
    }
    // if no character matches, return index of unknown
    return 0;
}

/*
 * Works on new test data
 */
string getMinimumSymbolErrorRateSpellingCorrection(string &line, double lambda)
{
    unsigned short bestCurCharIndex = 2;
    double logProbability;
    double logMaxProbability;
    double sum;

    string correctedLine;
    vector< pair<string, double> > Q_n_prev; // double value contains logarithmic probability (n-1)
    vector< pair<string, double> > Q_n_cur; // double value contains logarithmic probability
    vector< pair<string, double> > Qt_n_post; // double value contains logarithmic probability (n-1)

    // (pre)initialize Q_{n-1} for all characters c
    for(unsigned i = 0; i <= vocabLength; i++)
    {
        Q_n_prev.push_back(make_pair(vocab[i],0));
    }
    initQtPost(line, lambda, Qt_n_post);

    // parse sentence
    for (unsigned n = 0; n < line.length(); n = n + 1)
    {
        logMaxProbability = std::numeric_limits<int>::min();
        // iterate over every c and calculate p_n(c, x_1^N)
        for(unsigned c = 0; c <= vocabLength; c++)
        {
            sum = 0;
            // iterate over every c' and sum p(c|c')
            for(unsigned cPrime = 0; cPrime <= vocabLength; cPrime++)
            {           
                // this is SUM_c'( p(c|c') * Q_{n-1}(c') ) from slide 11
                sum += pow(exp(1.0), scores[cPrime][c] + Q_n_prev[cPrime].second);
            }
            logProbability = log(getPLambdaXnCn(line[n], vocab[c][0], lambda));
            double Q_n_value = logProbability + log(sum);
//            cout << "[SymbolErr] \tc: " << vocab[c] << ", index: " << c 
//                    << ", prob_sum: " << sum << ", logprob: " << logProbability
//                    << ", Q_n(c): " << logProbability + log(sum)
//                    << endl;
            Q_n_cur.push_back(make_pair(vocab[c], Q_n_value));
            if (Q_n_value + Qt_n_post[c].second > logMaxProbability)
            {
                logMaxProbability = Q_n_value + Qt_n_post[c].second;
                bestCurCharIndex  = c; // save arg max
            }
        }
        Q_n_prev = Q_n_cur;
        Q_n_cur.clear();

        if(bestCurCharIndex == unkToken)
        {
            correctedLine = correctedLine + line[n]; //remain symbol
        } 
        else
        {
            // rebuild the "corrected" sentence
            correctedLine = correctedLine + vocab[bestCurCharIndex]; 
        }
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
//            cout << "lineRandom : " << lineRandom << endl;
            lineCorrected = getMinimumSymbolErrorRateSpellingCorrection(lineRandom, lambda);
//            cout << "lineCorrected : " << lineCorrected << endl;
            xErrorAccuracy += getLineAccuracy(line, lineRandom) * line.length();                // = # of correct characters
            cErrorAccuracy += getLineAccuracy(line, lineCorrected) * line.length();             // = # of correct characters
            documentLength += line.length();
        }
        // = document's accuracy (instead of line's accuracy)
        xErrorAccuracy /= documentLength;                                                       
        // = document's accuracy (instead of line's accuracy)
        cErrorAccuracy /= documentLength;                                                       
        cout << "Lambda: " << lambda << " with error rate improvment: " <<1 - cErrorAccuracy + xErrorAccuracy << endl;
        cout << "The error rates are: X error rate " << 1 - xErrorAccuracy << ", C error rate " << 1 - cErrorAccuracy << endl;
    } 
    else
    {
        cout << "error opening test_data" << endl;
    }
}

int main (int argc, char *argv[])
{
    srand (time(NULL));
    init_vocab();                               //from simple_lm
    init_lm();                                  //from simple_lm

    cout << "1.b)" << endl;
    partA(0.9);
    return 0;
}
