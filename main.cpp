#include "main.h"
#include <iostream>

using namespace std;

int main_KL_3_4 () {
    App* app = new App();
    app->input();
    app->output();
    return 0;
}

int main() {

    Testing* test = new Testing(4, &main_KL_3_4);
    test->testing();

    return 0;
}
