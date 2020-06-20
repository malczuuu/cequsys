#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class solver_t {
private:
    /**
     * Represent A in the system of linear equations matrix form (A * x = b).
     */
    vector<double> _a_matr;

    /**
     * Represent b in the system of linear equations matrix form (A * x = b).
     */
    vector<double> _b_vect;

    /**
     * Since the algorithms reorders rows in matrix we to avoid moving large arrays the program just swaps the indexes.
     */
    vector<int> _inds;

    int _size;

    int _coords(int i, int j) const { return _inds[i] * _size + j; }

    int _coords(int i) const { return _inds[i]; }

    /**
     * Reorders row with the next first row which has nonzero i-diagonal if such row exists. Otherwise does nothing.
     */
    void _diag_fix(int i)
    {
        int index = i;
        for (int j = i; j < size(); ++j) {
            if (abs((double)get(j, i)) > abs((double)get(index, i))) {
                index = j;
            }
        }

        if (index != i) {
            swap(_inds[i], _inds[index]);
        }
    }

public:
    explicit solver_t(int size)
        : _size(size)
    {
        if (size > 0) {
            _a_matr.resize(size * size);
            _b_vect.resize(size);
            _inds.resize(size);
            for (int i = 0; i < size; ++i) {
                _inds[i] = i;
            }
        }
    }

    virtual ~solver_t() = default;

    const int& size() const { return _size; }

    const double& get(int i, int j) const { return _a_matr[_coords(i, j)]; }

    const double& get(int i) const { return _b_vect[_coords(i)]; }

    void set(int i, int j, double value) { _a_matr[_coords(i, j)] = value; }

    void set(int i, double value) { _b_vect[_coords(i)] = value; }

    void decompose_lu()
    {
        for (int i = 0; i < size(); ++i) {
            if (get(i, i) == 0.0) {
                _diag_fix(i);
                if (get(i, i) == 0.0) {
                    continue;
                }
            }

            for (int j = i + 1; j < size(); ++j) {
                double param = get(j, i) / get(i, i);
                for (int k = i; k < size(); ++k) {
                    set(j, k, get(j, k) - get(i, k) * param);
                }
                set(j, i, param);

                set(j, get(j) - get(i) * param);
            }
        }
    }

    /**
     *  { Ly = b
     *  { Ux = y
     *
     *  L = [1 0 0 0]    U = [* * * *]
     *      [* 1 0 0]        [0 * * *]
     *      [* * 1 0]        [0 0 * *]
     *      [* * * 1]        [0 0 0 *]
     *  INFO:
     *  When calculating Ly = b, there's no need to divide result by an element on main diagonal - there's always 1.
     */
    vector<double> solve_lu() const
    {
        vector<double> result(size());

        double sum = 0.0;
        vector<double> y_vect(size());
        y_vect[0] = get(0);
        for (int i = 1; i < size(); ++i) {
            for (int j = 0; j < i; ++j) {
                sum += get(i, j) * result[j];
            }
            y_vect[i] = get(i) - sum;
            sum = 0.0;
        }

        result[size() - 1] = y_vect[size() - 1] / get(size() - 1, size() - 1);

        for (int i = size() - 2; i >= 0; --i) {
            for (int j = i + 1; j < size(); ++j) {
                sum += get(i, j) * result[j];
            }
            result[i] = (y_vect[i] - sum) / get(i, i);
            sum = 0.0;
        }

        return result;
    }
};

static unique_ptr<solver_t> read_input(const string& filename);

static void write_output(const vector<double>& solution);

int main(int argc, char* argv[])
{
    unique_ptr<solver_t> solver = read_input("input.txt");

    solver->decompose_lu();
    vector<double> solution = solver->solve_lu();

    write_output(solution);
    return 0;
}

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

static string trim(string s)
{
    trim_inplace(s);
    return s;
}

static vector<string> split_string(string str, const string& separator)
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

static double fetch_number(const string& line) { return stod(line); }

static vector<double> fetch_numbers(const string& line)
{
    vector<string> numstrs;
    vector<double> nums;
    numstrs = split_string(line, " ");
    nums.reserve(numstrs.size());
    for (string& numstr : numstrs) {
        nums.push_back(fetch_number(numstr));
    }
    return nums;
}

static unique_ptr<solver_t> read_input(const string& filename)
{
    ifstream input;
    input.open(filename);

    string line;
    getline(input, line);
    vector<string> segments = split_string(line, ";");
    vector<double> matr_row = fetch_numbers(segments[0]);

    int size = matr_row.size();

    unique_ptr<solver_t> solver = make_unique<solver_t>(size);

    int row = 0;

    for (int i = 0; i < size; ++i) {
        solver->set(row, i, matr_row[i]);
    }

    double vect_item = fetch_number(segments[1]);
    solver->set(row, vect_item);

    ++row;

    while (getline(input, line)) {
        if (row >= size) {
            break;
        } else if (line.length() > 0) {
            segments = split_string(line, ";");
            matr_row = fetch_numbers(segments[0]);

            for (int i = 0; i < size; ++i) {
                solver->set(row, i, matr_row[i]);
            }

            vect_item = fetch_number(segments[1]);
            solver->set(row, vect_item);
            ++row;
        }
    }

    return solver;
}

static void write_output(const vector<double>& solution)
{
    if (solution.size() > 1) {
        for (int i = 0; i < solution.size() - 1; ++i) {
            cout << solution[i] << ";";
        }
        cout << solution[solution.size() - 1] << endl;
    } else if (solution.size() == 1) {
        cout << solution[0] << endl;
    }
}
