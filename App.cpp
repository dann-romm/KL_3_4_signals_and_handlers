#include "App.h"

App::App () {
    string name;
    cin >> name;
    this->tree = new ChildClass1(name);
}

void App::input () {
    this->tree->build_tree();
}

void App::output () {
    this->tree->output_tree(0);
    this->tree->find_objects();
}