#include "main.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;


ifstream in;
streambuf *cinbuf = cin.rdbuf(); //save old buf
ofstream out;
streambuf *coutbuf = cout.rdbuf(); //save old buf

void set_fin() { //redirect cin to input.txt
    in.open("testing-cases/test_input.txt", ios::in);
    cin.rdbuf(in.rdbuf());
}
void set_fout() { //redirect cout to output.txt
    out.open("testing-cases/test_output.txt", ios::out);
    cout.rdbuf(out.rdbuf());
}
void set_cin() { //reset to standard input again
    cin.rdbuf(cinbuf);
    in.close();
}
void set_cout() { //reset to standard output again
    cout.rdbuf(coutbuf);
    out.close();
}

int main_KL_3_4 () {
    App* app = new App();
    app->input();
    app->output();
    return 0;
}

void compare_testing_files (int test_case) {
    ifstream f1, f2;
    string line1, line2;
    stringstream message;

    stringstream test_output_file;
    test_output_file << "testing-cases/test_" << test_case << "_o.txt";

    f1.open(test_output_file.str(), ios::in);
    f2.open("testing-cases/test_output.txt", ios::in);

    int counter = 0;

    if (f1.eof()) {
        message << "пустой файл";
        throw invalid_argument(message.str());
    }

    while (!f1.eof() && !f2.eof()) {
        counter++;

        getline(f1, line1);
        getline(f2, line2);

        if (line1 != line2) {
            message << "несоответствие строки " << counter;
            message << "\nожидалось:" << line1 << "\nполучено: " << line2;
            f1.close();
            f2.close();
            throw invalid_argument(message.str());
        }
    }

    if (!f1.eof()) {
        message << "количество строк меньше ожидаемого";
        f1.close();
        f2.close();
        throw invalid_argument(message.str());
    } else if (!f2.eof()) {
        f1.close();
        f2.close();
        message << "количество строк больше ожидаемого";
        throw invalid_argument(message.str());
    }

    message.flush();
    test_output_file.flush();
    f1.close();
    f2.close();
};

void copy_testing_file (int test_case) {
    ifstream f1;
    ofstream f2;

    string buffer;

    stringstream test_input_file;
    test_input_file << "testing-cases/test_" << test_case << "_i.txt";

    f1.open(test_input_file.str(), ios::in);
    f2.open("testing-cases/test_input.txt", ios::out);

    while (!f1.eof()) {
        buffer += (char)f1.get();
    }
    buffer.erase(buffer.end() - 1);
    f2 << buffer;

    test_input_file.flush();
    f1.close();
    f2.close();
}

void clear_test_files () {
    ofstream f1, f2;
    f1.open("testing-cases/test_input.txt", ios::out | ios::trunc);
    f2.open("testing-cases/test_output.txt", ios::out | ios::trunc);
    f1.close();
    f2.close();
}

void testing (int epochs, int (*function)()) { //

    set_fin();
    set_fout();
    clear_test_files();

    for (int test_case = 1; test_case <= epochs; test_case++) {

        copy_testing_file(test_case);

        main_KL_3_4();

        try {
            compare_testing_files(test_case);

        } catch(invalid_argument &ex) {
            set_cout();
            cout << "ошибка на тесте " << test_case << ":\n";
            cout << ex.what();
            set_fout();
        }

        clear_test_files();

    }
}


int main() {

    testing(2, &main_KL_3_4);

    return 0;
}
