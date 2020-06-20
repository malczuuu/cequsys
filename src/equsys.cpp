#include "equsys.hpp"
#include <cmath>

using namespace std;

void equsys_t::resize(int rows, int cols)
{
    _a_matr.resize(rows, cols);
    _b_vect.resize(rows);
    _inds.resize(rows);
    for (int i = 0; i < rows; ++i) {
        _inds[i] = i;
    }
}

int equsys_t::equs() const { return _a_matr.rows(); }

int equsys_t::vars() const { return _a_matr.cols(); }

double equsys_t::get(int i, int j) const { return _a_matr.get(_inds[i], j); }

void equsys_t::set(int i, int j, double value) { _a_matr.set(_inds[i], j, value); }

double equsys_t::get(int i) const { return _b_vect[_inds[i]]; }

void equsys_t::set(int i, double value) { _b_vect[_inds[i]] = value; }

void equsys_t::diag_fix(int ind)
{
    int chosen_ind = ind;
    for (int i = ind; i < equs(); ++i) {
        if (abs((double)get(i, ind)) > abs((double)get(chosen_ind, ind))) {
            chosen_ind = i;
        }
    }

    if (chosen_ind != ind) {
        swap(_inds[ind], _inds[chosen_ind]);
    }
}

void decolu(equsys_t& equsys)
{
    for (int i = 0; i < equsys.equs(); ++i) {
        if (equsys.get(i, i) == 0.0) {
            equsys.diag_fix(i);
            if (equsys.get(i, i) == 0.0) {
                continue;
            }
        }

        for (int j = i + 1; j < equsys.equs(); ++j) {
            double param = equsys.get(j, i) / equsys.get(i, i);
            for (int k = i; k < equsys.vars(); ++k) {
                equsys.set(j, k, equsys.get(j, k) - equsys.get(i, k) * param);
            }
            equsys.set(j, i, param);

            equsys.set(j, equsys.get(j) - equsys.get(i) * param);
        }
    }
}

vector<double> equsys_t::solvelu() const
{

    vector<double> result(equs());

    /**
        { Ly = b
        { Ux = y

        L = [1 0 0 0]    U = [* * * *]
            [* 1 0 0]        [0 * * *]
            [* * 1 0]        [0 0 * *]
            [* * * 1]        [0 0 0 *]
        INFO:
        When calculating Ly = b, there's no need to divide result by an
        element on main diagonal - there's always 1.
    */

    double sum = 0.0;
    vector<double> y_vect(equs());
    y_vect[0] = get(0);
    for (int i = 1; i < equs(); ++i) {
        for (int j = 0; j < i; ++j) {
            sum += get(i, j) * result[j];
        }
        y_vect[i] = get(i) - sum;
        sum = 0.0;
    }

    result[equs() - 1] = y_vect[equs() - 1] / get(equs() - 1, equs() - 1);

    for (int i = equs() - 2; i >= 0; --i) {
        for (int j = i + 1; j < equs(); ++j) {
            sum += get(i, j) * result[j];
        }
        result[i] = (y_vect[i] - sum) / get(i, i);
        sum = 0.0;
    }

    return result;
}
