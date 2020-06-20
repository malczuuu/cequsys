#include "loader.hpp"
#include "equsys.hpp"
#include "stringutil.hpp"

using namespace std;

void load_input(ifstream& input, equsys_t& equsys)
{
    string line;
    getline(input, line);
    vector<string> segments = split_string(line, ";");
    vector<double> matr_row = fetch_numbers(segments[0]);
    int dimension = matr_row.size();

    equsys.resize(dimension, dimension);

    int row = 0;

    for (int i = 0; i < dimension; ++i) {
        equsys.set(row, i, matr_row[i]);
    }

    double vect_item = fetch_number(segments[1]);
    equsys.set(row, vect_item);

    ++row;

    while (getline(input, line)) {
        if (row >= dimension) {
            break;
        } else if (line.length() > 0) {
            segments = split_string(line, ";");
            matr_row = fetch_numbers(segments[0]);

            for (int i = 0; i < dimension; ++i) {
                equsys.set(row, i, matr_row[i]);
            }

            vect_item = fetch_number(segments[1]);
            equsys.set(row, vect_item);
            ++row;
        }
    }
}