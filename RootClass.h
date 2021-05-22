#ifndef rootclass_h
#define rootclass_h

#include <iostream>
#include <vector>
#include <string.h>
using namespace std;


class RootClass{
private:
    string name;
    RootClass* parent;
    int mode;
    vector<RootClass*> child_list;
public:
    RootClass(string name, RootClass* parent, int mode);
    void testing();
    void output_tree(int depth);

    void find_objects();
    RootClass* find_by_name(string name);
    RootClass* find_by_path(string path);

    void set_name(string name);
    string get_name();
};

class ChildClass1: public RootClass{
public:
    ChildClass1(string name);
    void build_tree();
};

class ChildClass2: private RootClass{
public:
    ChildClass2(string name, RootClass* parent, int mode);
};

class ChildClass3: private RootClass{
public:
    ChildClass3(string name, RootClass* parent, int mode);
};

class ChildClass4: private RootClass{
public:
    ChildClass4(string name, RootClass* parent, int mode);
};

class ChildClass5: private RootClass{
public:
    ChildClass5(string name, RootClass* parent, int mode);
};

class ChildClass6: private RootClass{
public:
    ChildClass6(string name, RootClass* parent, int mode);
};


#endif