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

    message.str(string());
    test_output_file.str(string());
    f1.close();
    f2.close();

    throw counter;
};

void copy_testing_file (int epochs) {
    ifstream f1;
    ofstream f2;

    string buffer, path;
    stringstream test_input_file;

    f2.open("testing-cases/test_input.txt", ios::out);

    for (int test_case = 1; test_case <= epochs; test_case++) {

        test_input_file << "testing-cases/test_" << test_case << "_i.txt";
        path = test_input_file.str();
        test_input_file.str(string());

        f1.open(path, ios::in);

        while (!f1.eof()) {
            getline(f1, buffer);
            f2 << buffer << "\n";
        }

        f1.close();

    }

    f2.close();

}

void clear_test_files (bool all_to_clear) {
    ofstream f2;
    f2.open("testing-cases/test_output.txt", ios::out | ios::trunc);
    f2.close();

    if (all_to_clear) {
        ofstream f1;
        f1.open("testing-cases/test_input.txt", ios::out | ios::trunc);
        f1.close();
    }
}

void testing (int epochs, int (*function)()) { //

    set_fin();
    set_fout();
    clear_test_files(true);
    copy_testing_file(epochs);

    for (int test_case = 1; test_case <= epochs; test_case++) {

        main_KL_3_4();

        try {
            compare_testing_files(test_case);

        } catch(invalid_argument &ex) {
            set_cout();
            cout << "ошибка на тесте " << test_case << ":\n";
            cout << ex.what();
            cout << "\n";
            set_fout();
        } catch(int counter) {
            set_cout();
            cout << "тест " << test_case << " пройден, " << counter << " строк(и) верны\n";
            set_fout();
        }

        clear_test_files(false);

    }
}

int main() {

    testing(3, &main_KL_3_4);

    return 0;
}
