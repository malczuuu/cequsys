#ifndef LOADER_HPP
#define LOADER_HPP

#include "matrix.hpp"
#include <fstream>
#include <vector>

void load_input(std::ifstream& input, matrix<double>& a_matr, std::vector<double>& b_vect);

#endif
