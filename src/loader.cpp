#include "loader.hpp"
#include "stringutil.hpp"

using namespace std;

void load_input(ifstream& input, matrix<double>& a_matr, vector<double>& b_vect)
{
    string line;
    getline(input, line);
    vector<string> segments = split_string(line, ";");
    vector<double> matr_row = fetch_numbers(segments[0]);
    int dimension = matr_row.size();

    a_matr.resize(dimension, dimension);
    b_vect.resize(dimension);

    int row = 0;

    for (int i = 0; i < dimension; ++i) {
        a_matr.set(row, i, matr_row[i]);
    }

    double vect_item = fetch_number(segments[1]);
    b_vect[row] = vect_item;

    ++row;

    while (getline(input, line)) {
        if (row >= dimension) {
            break;
        } else if (line.length() > 0) {
            segments = split_string(line, ";");
            matr_row = fetch_numbers(segments[0]);

            for (int i = 0; i < dimension; ++i) {
                a_matr.set(row, i, matr_row[i]);
            }

            vect_item = fetch_number(segments[1]);
            b_vect[row] = vect_item;
            ++row;
        }
    }
}