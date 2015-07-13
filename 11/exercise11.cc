#include <iostream>
#include <fstream>
#include <string>
#include <climits>

#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))
using namespace std;

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
int numberOfErrorsInSentence(string &sentence1, string &sentence2)
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

    double numberOfErrors         = numberOfErrorsInSentence(hypothesisSentence, referenceSentence);
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

int main (int argc, char *argv[])
{
    string testShort = "dies bla ein test";
    string testLong  = "test dies blub ein";
    double test = getPER(testShort, testLong);
    cout << test << endl;
    return 1;
}
