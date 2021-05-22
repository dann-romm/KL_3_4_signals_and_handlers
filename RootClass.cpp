#include "RootClass.h"


RootClass::RootClass (string name, RootClass* parent, int mode) {
    this->name = name;
    this->parent = parent;
    this->mode = mode;
    this->child_list = {};
    if (parent != nullptr) {
        parent->child_list.push_back(this);
    }
}

void RootClass::testing () {
    if (this->parent == nullptr) {
        cout << "Test result\nThe object " << this->name << " is ready";
    } else if (this->mode > 0) {
        cout << endl << "The object " << this->name << " is ready";
    } else {
        cout << endl << "The object " << this->name << " is not ready";
    }
    for (int i=0; i < child_list.size(); ++i) {
        child_list[i]->testing();
    }
}

void RootClass::output_tree (int depth) {
    if (this->parent == nullptr) {
        cout << "Object tree\n" << this->name;
    } else {
        cout << endl;
        for (int i=0; i < depth; i++) {cout << "    ";}
        cout << this->name;
    }
    for (int i=0; i < child_list.size(); ++i) {
        child_list[i]->output_tree(depth + 1);
    }
}

RootClass* RootClass::find_by_path (string path) {
    if ("//" == path.substr(0, 2)) {
        return this->find_by_name(path.substr(2, path.length()));
    }

    vector<string> parsed_path = {};
    int word_len = 0;
    int last_slash = 0;

    for (int i=1; i<path.length(); ++i) {
        word_len++;
        if ((char)path[i] == '/') {

            parsed_path.push_back(path.substr(i-word_len+1, word_len-1));
            word_len = 0;
            last_slash = i;
        }
    }
    parsed_path.push_back(path.substr(last_slash+1, word_len));


    if (parsed_path.size() == 0) {
        return this;
    }

    RootClass* q = this;
    bool key = true;

    for (int i=1; i<parsed_path.size(); ++i) {

        for (int j=0; j < q->child_list.size(); ++j) {

            if (q->child_list[j]->name == parsed_path[i]) {
                q = q->child_list[j];
                key = false;
                break;
            }
        }
        if (key) { return nullptr; }

    }
    return q;
}

RootClass* RootClass::find_by_name (string name) {
    if (this->name == name) {
        return this;
    } else {
        RootClass* temp;
        for (int i=0; i < child_list.size(); ++i) {
            temp = child_list[i]->find_by_name(name);
            if (temp) { return temp; }
        }
    }
    return nullptr;
}

void RootClass::find_objects () {
    string path;
    RootClass* object;

    cin >> path;

    while (path != "//") {

        object = this->find_by_path(path);

        if (object != nullptr) {
            cout << "\n" << path << " Object name: " << object->name;
        } else {
            cout << "\n" << path << " Object not found";
        }

        cin >> path;
    }

}

void ChildClass1::build_tree () {
    ChildClass2* class2;
    ChildClass3* class3;
    ChildClass4* class4;
    ChildClass5* class5;
    ChildClass6* class6;

    string name, path;

    short choice;
    int mode;

    while (true) {
        cin >> path;
        if (path == "endtree") { break; }
        cin >> name >> choice >> mode;
        switch (choice) {
            case (2):
                class2 = new ChildClass2(name, this->find_by_path(path), mode);
                break;
            case (3):
                class3 = new ChildClass3(name, this->find_by_path(path), mode);
                break;
            case (4):
                class4 = new ChildClass4(name, this->find_by_path(path), mode);
                break;
            case (5):
                class5 = new ChildClass5(name, this->find_by_path(path), mode);
                break;
            case (6):
                class6 = new ChildClass6(name, this->find_by_path(path), mode);
                break;
        }
    }
}

void RootClass::set_name (string name) {
    this->name = name;
}

string RootClass::get_name () {
    return this->name;
}


ChildClass1::ChildClass1(string name):RootClass(name, nullptr, 1){}
ChildClass2::ChildClass2(string name, RootClass* parent, int mode):RootClass(name, parent, mode){}
ChildClass3::ChildClass3(string name, RootClass* parent, int mode):RootClass(name, parent, mode){}
ChildClass4::ChildClass4(string name, RootClass* parent, int mode):RootClass(name, parent, mode){}
ChildClass5::ChildClass5(string name, RootClass* parent, int mode):RootClass(name, parent, mode){}
ChildClass6::ChildClass6(string name, RootClass* parent, int mode):RootClass(name, parent, mode){}
