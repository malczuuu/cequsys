#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>

template <typename T> class matrix {
private:
    std::vector<T> _content;
    int _rows;
    int _cols;

public:
    matrix()
        : matrix(0, 0)
    {
    }

    matrix(int rows, int cols)
        : _rows(rows)
        , _cols(cols)
    {
    }

    matrix(const matrix& original)
        : _content(original._content)
        , _rows(original._rows)
        , _cols(original._cols)
    {
    }

    virtual ~matrix() {}

    void resize(int rows, int cols)
    {
        _content.resize(rows * cols);
        _rows = rows;
        _cols = cols;
    }

    const int& cols() const { return _cols; }

    const int& rows() const { return _rows; }

    T get(int i, int j) const { return _content[i * _cols + j]; }

    void set(int i, int j, T value) { _content[i * _cols + j] = value; }
};

#endif
