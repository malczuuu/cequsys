#include "equsys.hpp"
#include "loader.hpp"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    ifstream input;
    input.open("input.txt");
    equsys_t equsys;
    try {
        load_input(input, equsys);
    } catch (invalid_argument& e) {
        cerr << "[ERROR] " << e.what() << endl;
    }
    input.close();

    for (int i = 0; i < equsys.equs(); ++i) {
        for (int j = 0; j < equsys.vars(); ++j) {
            cout << equsys.get(i, j) << " ";
        }
        cout << "; " << equsys.get(i) << endl;
    }

    decolu(equsys);

    cout << "LU" << endl;

    for (int i = 0; i < equsys.equs(); ++i) {
        for (int j = 0; j < equsys.vars(); ++j) {
            cout << equsys.get(i, j) << " ";
        }
        cout << "; " << equsys.get(i) << endl;
    }

    vector<double> result = equsys.solvelu();

    for (double x_i : result) {
        cout << x_i << " ";
    }
    cout << endl;

    return 0;
}
