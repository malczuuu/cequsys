#include "loader.hpp"
#include "matrix.hpp"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    ifstream input;
    input.open("input.txt");
    matrix<double> a_matr;
    vector<double> b_vect;
    try {
        load_input(input, a_matr, b_vect);
    } catch (invalid_argument& e) {
        cerr << "[ERROR] " << e.what() << endl;
    }
    input.close();

    for (int i = 0; i < a_matr.rows(); ++i) {
        for (int j = 0; j < a_matr.cols(); ++j) {
            cout << a_matr.get(i, j) << " ";
        }
        cout << "; " << b_vect[i] << endl;
    }

    return 0;
}