#ifndef TRIM_HPP
#define TRIM_HPP

#include <string>
#include <vector>

std::string trim(std::string s);

std::vector<std::string> split_string(std::string str, std::string separator);

double fetch_number(const std::string& line);

std::vector<double> fetch_numbers(const std::string& line);

#endif
