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
    string data;
    string cmd;
    string lm_order = "2";

    if(argc > 2) {
        data     = argv[1];
        lm_order = argv[2];
    }
    else {
        cout << "Exactly 2 parameters are required: "
                << "training_data_file[e.g., tc_star] "  
                << "lm_order." << endl;
        return -1;
    }

    if (atoi(lm_order.c_str()) > 9) {
        cout << "SRILM only allows LM order of maximum 9." << endl;
        return -1;
    }

    // bogus file opening / check for existence
    ifstream data_file(data.c_str());
    if (!data_file.is_open()) {
        cout << "Could not find training data file. Exiting." << endl;
        return -1;
    }
    data_file.close();

    cmd = string("ngram-count -text ") + data + string(" -order ") + lm_order +
            string(" -kndiscount") + lm_order + string(" -lm lm_ex_3_e.out");
    int ret = system(cmd.c_str()); 
    
    cout << endl << "Perplexity of training data " << data 
            << " is the ppl value below: " << endl; 

    cmd = string("ngram -order ") + lm_order + string(" -lm lm_ex_3_e.out") +
            string(" -ppl lm_ex_3_e.out");
    ret = system(cmd.c_str()); 
    return 0;
}
