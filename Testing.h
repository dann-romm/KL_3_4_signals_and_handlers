#ifndef KL_3_4_SIGNALS_AND_HANDLERS_TESTING_H
#define KL_3_4_SIGNALS_AND_HANDLERS_TESTING_H

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

class Testing {
public:
    Testing(int epochs, int (*function)());
    void testing();
private:
    ifstream in;
    ofstream out;
    streambuf *cinbuf;
    streambuf *coutbuf;

    string input_path, output_path, test_path;

    int epochs, counter;
    int (*function)();

    void set_fin(); //redirect cin to input.txt
    void set_fout(); //redirect cout to output.txt
    void set_cin(); //reset to standard input again
    void set_cout();  //reset to standard output again

    void clear_test_files (bool all_to_clear);
    void copy_testing_file();
    void compare_testing_files (int test_case);
};


#endif //KL_3_4_SIGNALS_AND_HANDLERS_TESTING_H
