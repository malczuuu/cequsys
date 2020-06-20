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
        : _rows(0)
        , _cols(0)
    {
    }

    matrix(int rows, int cols)
        : _rows(rows)
        , _cols(cols)
    {
        int size = rows * cols;
        if (size > 0) {
            _content.resize(size);
        }
    }

    matrix(int dimension)
        : _rows(dimension)
        , _cols(dimension)
    {
        int size = dimension * dimension;
        if (size > 0) {
            _content.resize(size);
        }
    }

    matrix(const matrix& original)
        : _content(original._content)
        , _rows(original._rows)
        , _cols(original._cols)
    {
    }

    virtual ~matrix() = default;

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
