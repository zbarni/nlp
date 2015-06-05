// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
// Make sure that "ngram-count" and "ngram" SRILM binaries are in your PATH.
// -------------------------------------------------------------------------
// -------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cmath>
#include <cstdlib>
using namespace std;

int main (int argc, char *argv[]) {
    string line;
    string lm_filename;
    int N = -1;
    double PP = 0;

    // argument stuff
    if(argc > 1) {
        lm_filename = argv[1];
    }
    else {
        cout << "Please give the path to the LM file." << endl;
        return -1;
    }

    // open LM file
    ifstream lm_file(lm_filename.c_str());
    if (!lm_file.is_open()) {
        cout << "Could not open LM file. Exiting." << endl;
        return -1;
    }

    // get N = 2-gram counts
    while(getline (lm_file,line) ) {
        if (line.find("ngram 2") != string::npos) {
            string N_str = line.substr(line.find("=") + 1);
            // to avoid c++11
            N = atoi(N_str.c_str());
            break;
        }
    }

    // check for bigram counts
    if (N == -1) {
        cout << "Incorrect LM file. Could not find number of bigrams." << endl;
        lm_file.close();
        return -1;
    }

    // compute perplexity
    while(getline (lm_file,line) ) {
        // scroll down till bigrams
        if (line.find("2-grams") == string::npos) {
            continue;
        }
        while(getline (lm_file,line)) {
            string p_str = line.substr(0,line.find(" "));
            double p     = atof(p_str.c_str());
            PP          += p;
        }
    }

    // postprocessing and output
    PP = -PP;
    cout << "Number of bigrams: " << N << endl;
    cout << "Perplexity of language model is: " << pow(10, PP / N) << endl;
    lm_file.close();
    return 0;
}
