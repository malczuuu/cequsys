#ifndef LU_MATR_HPP
#define LU_MATR_HPP

#include "matrix.hpp"

class equsys_t {
private:
    matrix<double> _a_matr;
    std::vector<double> _b_vect;

    /**
     * Contains row-indexes of matrix because further calculation may involve reordering rows.
     */
    std::vector<int> _inds;

public:
    void resize(int rows, int cols);

    /**
     * Gets number of equations in equation system matrix (which corresponds with number of rows in the matrix itself).
     */
    int equs() const;

    /**
     * Gets number of variables in equation system matrix (which corresponds with number of columns in the matrix
     * itself).
     */
    int vars() const;

    double get(int i, int j) const;

    void set(int i, int j, double value);

    double get(int i) const;

    void set(int i, double value);

    /**
     * Fixes diagonal element being 0 by reordering equation system's rows.
     */
    void diag_fix(int i);

    std::vector<double> solvelu() const;
};

/**
 * Performs the LU decomposition on equation system matrix and vector.
 */
void decolu(equsys_t& equsys);

#endif
