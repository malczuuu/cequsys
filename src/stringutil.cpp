#include "stringutil.hpp"
#include <algorithm>
#include <vector>

using namespace std;

static inline void ltrim_inplace(string& s)
{
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](int ch) { return !isspace(ch); }));
}

static inline void rtrim_inplace(string& s)
{
    s.erase(find_if(s.rbegin(), s.rend(), [](int ch) { return !isspace(ch); }).base(), s.end());
}

static inline void trim_inplace(string& s)
{
    ltrim_inplace(s);
    rtrim_inplace(s);
}

string trim(string s)
{
    trim_inplace(s);
    return s;
}

vector<string> split_string(string str, string separator)
{
    vector<string> result;
    int i;
    while ((i = str.find_first_of(separator)) != string::npos) {
        result.push_back(trim(str.substr(0, i)));
        str = trim(str.substr(i + 1));
    }
    result.push_back(str);
    return result;
}

double fetch_number(const string& line) { return stod(line); }

vector<double> fetch_numbers(const string& line)
{
    vector<string> numstrs;
    vector<double> nums;
    numstrs = split_string(line, " ");
    nums.reserve(numstrs.size());
    for (int i = 0; i < numstrs.size(); ++i) {
        nums.push_back(fetch_number(numstrs[i]));
    }
    return nums;
}
