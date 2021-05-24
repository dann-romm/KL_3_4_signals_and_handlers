#ifndef rootclass_h
#define rootclass_h

#include <iostream>
#include <vector>
using namespace std;

class RootClass;

typedef void (RootClass::*TYPE_SIGNAL) (string &); // Определим указатель на метод отправки сигнала

typedef void (RootClass::*TYPE_HANDLER) (string); // Определим указатель на метод получения сигнала

#define SIGNAL_D(signal_f) (TYPE_SIGNAL)(& signal_f) // Преобразуем метод signal_f к типу TYPE_SIGNAL макросом SIGNAL_D

#define HANDLER_D(handler_f) (TYPE_HANDLER)(& handler_f) // Преобразуем метод handler_f к типу TYPE_HANDLER макросом HANDLER_D

//class Connection{
//public:
//    int id;
//    TYPE_SIGNAL signal;
//    TYPE_HANDLER handler;
//    RootClass* sender;
//    RootClass* target;
//    Connection(int id, RootClass* sender, RootClass* target, TYPE_SIGNAL signal, TYPE_HANDLER handler);
//};

struct Connection {
    int id;
    TYPE_SIGNAL signal;
    TYPE_HANDLER handler;
    RootClass* sender;
    RootClass* target;
};

class RootClass{
private:
    string name;
    RootClass* parent;
    int mode;
    vector<RootClass*> child_list;
    vector<Connection*> connection_list;
public:
    RootClass(string name, RootClass* parent, int mode);
    void testing();
    void output_tree(int depth);

    void find_objects();
    RootClass* find_by_name(string name);
    RootClass* find_by_path(string path);

    void set_connection(int id, RootClass* sender, RootClass* target, TYPE_SIGNAL signal, TYPE_HANDLER handler);
    void delete_connection(Connection* connection);
    void emit_signals(TYPE_SIGNAL signal, string & message);

    void signal_type1(string & message);
    void handler_type1(string message);
    void signal_type2(string & message);
    void handler_type2(string message);
    void signal_type3(string & message);
    void handler_type3(string message);

    void set_name(string name);
    string get_name();
};

class ChildClass1: public RootClass{
public:
    ChildClass1(string name);
    void build_tree();
    void set_connects();
    void send_signals();
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