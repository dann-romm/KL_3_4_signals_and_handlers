#include "App.h"

App::App () {
    string name;
    cin >> name;
    this->tree = new ChildClass1(name);
}

void App::input () {
    this->tree->build_tree();
    this->tree->output_tree(0);
}

void App::output () {
    this->tree->set_connects();
    this->tree->send_signals();
}