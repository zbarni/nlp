#include <iostream>
#include <fstream>
#include <string>
#include "dictionary.hh"
using namespace std;

int main (int argc, char *argv[]) {
    int n;
    string line;
    string param;
    string word;
    bool newWord;
    bool firstWord = true;
    char c;
    Dict dict;

    if(argc > 1)
    {
        param = argv[1];
        n = stoi(param);
    }
    else 
    {
        n = 0;
    }
    if (n) { }

    ifstream myfile ("alice.txt");
    if (myfile.is_open())
    {
        while(getline (myfile,line))
        {
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
                            dict.insert(word);
                        }
                        else
                        {
                            firstWord = false;
                        }
                        word = c;
                        if ((c>='a') && (c<='z'))
                        {
                            newWord = false;
                        }
                    }
                    else
                    {
                        if ((c>='a') && (c<='z'))
                        {
                            word += c;
                        }
                        else
                        {
                            dict.insert(word);
                            word = c;
                            newWord = true;
                        }
                    }
                }
                else
                {
                    newWord = true;
                }
            }
        }
        dict.insert(word);
        myfile.close();
    }
    else 
    {
        cout << "Unable to open file";
    }
    cout << dict.find(1) << std::endl;
    cout << dict.find(7) << std::endl;
    cout << dict.getIndex("get") << endl;
    cout << dict.getIndex("alice") << endl;
    cout << dict.getIndex("lewis") << endl;

    return 0;
}
