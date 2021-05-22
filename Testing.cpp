#include "Testing.h"

Testing::Testing(int epochs, int (*function)()) {
    this->epochs = epochs;
    this->function = function;
    this->counter = 0;

    cinbuf = cin.rdbuf();
    coutbuf = cout.rdbuf();

    input_path = "testing-cases/test_input.txt";
    output_path = "testing-cases/test_output.txt";
    test_path = "testing-cases/test_";
}

void Testing::set_fin() {
    in.open(input_path, ios::in);
    cin.rdbuf(in.rdbuf());
}
void Testing::set_fout() {
    out.open(output_path, ios::out);
    cout.rdbuf(out.rdbuf());
}
void Testing::set_cin() {
    cin.rdbuf(cinbuf);
    in.close();
}
void Testing::set_cout() {
    cout.rdbuf(coutbuf);
    out.close();
}

void Testing::clear_test_files(bool all_to_clear) {
    ofstream f2;
    f2.open(output_path, ios::out | ios::trunc);
    f2.close();

    if (all_to_clear) {
        ofstream f1;
        f1.open(input_path, ios::out | ios::trunc);
        f1.close();
    }
}

void Testing::copy_testing_file() {
    ifstream f1;
    ofstream f2;

    string buffer, path;
    stringstream test_input_file;

    f2.open(input_path, ios::out);

    for (int test_case = 1; test_case <= epochs; test_case++) {

        test_input_file << test_path << test_case << "_i.txt";
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

void Testing::compare_testing_files(int test_case) {
    ifstream f1, f2;
    string line1, line2;
    stringstream message;

    stringstream test_output_file;
    test_output_file << test_path << test_case << "_o.txt";

    f1.open(test_output_file.str(), ios::in);
    f2.open(output_path, ios::in);

    counter = 0;

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
}

void Testing::testing() {

    bool case_passed;

    set_fin();
    set_fout();
    clear_test_files(true);
    copy_testing_file();

    for (int test_case = 1; test_case <= epochs; test_case++) {

        case_passed = false;
        function();

        try {
            compare_testing_files(test_case);
            case_passed = true;

        } catch(invalid_argument &ex) {
            set_cout();
            cout << "тест " << test_case << " ошибка: ";
            cout << ex.what();
            cout << "\n";
            set_fout();
        }

        if (case_passed) {
            set_cout();
            cout << "тест " << test_case << " пройден, " << counter << " строк(и) верны\n";
            set_fout();
        }
        clear_test_files(false);
    }
    clear_test_files(true);
    set_cin();
    set_cout();
}
