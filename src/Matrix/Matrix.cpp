/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Matrix
*/

#include "Matrix.hpp"
#include <iostream>

namespace RayTracer {
    Matrix::Matrix()
    {
    }

    Matrix::Matrix(
        int _rows,
        int _cols
    ) : _rows(_rows),
        _cols(_cols)
    {
        _data.resize(_rows, std::vector<double>(_cols, 0.0));
    }

    Matrix::Matrix(
        int _rows,
        int _cols,
        double initialValue
    ) : _rows(_rows),
        _cols(_cols)
    {
        _data.resize(_rows, std::vector<double>(_cols, initialValue));
    }

    Matrix::~Matrix()
    {
    }

    int Matrix::numRows() const
    {
        return _rows;
    }

    int Matrix::numCols() const
    {
        return _cols;
    }

    Matrix Matrix::operator+(const Matrix &other)
    {
        if (_rows != other._rows || _cols != other._cols)
            throw std::invalid_argument("Matrix error");
        Matrix result(_rows, _cols);
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < _cols; j++) {
                result._data[i][j] = _data[i][j] + other._data[i][j];
            }
        }
        return result;
    }

    Matrix &Matrix::operator+=(const Matrix &other)
    {
        if (_rows != other._rows || _cols != other._cols)
            throw std::invalid_argument("Matrix error");
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < _cols; j++) {
                _data[i][j] += other._data[i][j];
            }
        }
        return *this;
    }

    Matrix Matrix::operator-(const Matrix &other) const
    {
        if (_rows != other._rows || _cols != other._cols)
            throw std::invalid_argument("Matrix error");
        Matrix result(_rows, _cols);
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < _cols; j++) {
                result._data[i][j] = _data[i][j] - other._data[i][j];
            }
        }
        return result;
    }

    Matrix &Matrix::operator-=(const Matrix &other)
    {
        if (_rows != other._rows || _cols != other._cols)
            throw std::invalid_argument("Matrix error");
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < _cols; j++) {
                _data[i][j] -= other._data[i][j];
            }
        }
        return *this;
    }

    Matrix Matrix::operator*(const Matrix &other) const
    {
        if (_cols != other._rows)
            throw std::invalid_argument("Matrix error");
        Matrix result(_rows, other._cols);
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < other._cols; j++) {
                for (int k = 0; k < _cols; k++) {
                    result._data[i][j] += _data[i][k] * other._data[k][j];
                }
            }
        }
        return result;
    }

    Matrix &Matrix::operator*=(const Matrix &other)
    {
        if (_cols != other._rows)
            throw std::invalid_argument("Matrix error");
        Matrix result(_rows, other._cols);
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < other._cols; j++) {
                for (int k = 0; k < _cols; k++) {
                    result._data[i][j] += _data[i][k] * other._data[k][j];
                }
            }
        }
        _data = std::move(result._data);
        _cols = other._cols;
        return *this;
    }

    Matrix Matrix::operator*(double scalar) const
    {
        Matrix result(_rows, _cols);
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < _cols; j++) {
                result._data[i][j] = _data[i][j] * scalar;
            }
        }
        return result;
    }

    Matrix &Matrix::operator*=(double scalar)
    {
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < _cols; j++) {
                _data[i][j] *= scalar;
            }
        }
        return *this;
    }

    Matrix Matrix::operator/(double scalar) const
    {
        if (scalar == 0)
            throw std::invalid_argument("Matrix error");
        Matrix result(_rows, _cols);
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < _cols; j++) {
                result._data[i][j] = _data[i][j] / scalar;
            }
        }
        return result;
    }

    Matrix &Matrix::operator/=(double scalar)
    {
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < _cols; j++) {
                _data[i][j] /= scalar;
            }
        }
        return *this;
    }

    Matrix &Matrix::operator=(const Matrix &other)
    {
        if (this != &other) {
            _rows = other._rows;
            _cols = other._cols;
            _data = other._data;
        }
        return *this;
    }

    Matrix &Matrix::operator=(Matrix &&other)
    {
        if (this != &other) {
            _rows = other._rows;
            _cols = other._cols;
            _data = std::move(other._data);
        }
        return *this;
    }

    Vector3D Matrix::operator*(const Vector3D &vector) const
    {
        if (_cols < 3)
            throw std::invalid_argument("Matrix error");
        Vector3D result;
        result._x = _data[0][0] * vector._x + _data[0][1] * vector._y + _data[0][2] * vector._z;
        result._y = _data[1][0] * vector._x + _data[1][1] * vector._y + _data[1][2] * vector._z;
        result._z = _data[2][0] * vector._x + _data[2][1] * vector._y + _data[2][2] * vector._z;
        return result;
    }

    Point3D Matrix::operator*(const Point3D &point) const
    {
        if (_cols != 4)
            throw std::invalid_argument("Matrix error");
        Point3D result;
        result._x = _data[0][0] * point._x + _data[0][1] * point._y + _data[0][2] * point._z + _data[0][3];
        result._y = _data[1][0] * point._x + _data[1][1] * point._y + _data[1][2] * point._z + _data[1][3];
        result._z = _data[2][0] * point._x + _data[2][1] * point._y + _data[2][2] * point._z + _data[2][3];
        return result;
    }

    double &Matrix::operator()(int row, int col)
    {
        if (row < 0 || row >= _rows || col < 0 || col >= _cols)
            throw std::invalid_argument("Matrix error");
        return _data[row][col];
    }

    Matrix Matrix::inverse()
    {
        if (_rows != _cols)
            throw std::invalid_argument("Matrix error");
        Matrix result(_rows, _cols, 0.0);
        for (int i = 0; i < _rows; i++) {
            result._data[i][i] = 1;
        }
        for (int i = 0; i < _rows; i++) {
            double pivot = _data[i][i];
            for (int j = 0; j < _cols; j++) {
                _data[i][j] /= pivot;
                result._data[i][j] /= pivot;
            }
            for (int k = 0; k < _rows; k++) {
                if (k != i) {
                    double factor = _data[k][i];
                    for (int j = 0; j < _cols; j++) {
                        _data[k][j] -= factor * _data[i][j];
                        result._data[k][j] -= factor * result._data[i][j];
                    }
                }
            }
        }
        _data = std::move(result._data);
        return *this;
    }

    Matrix Matrix::transpose()
    {
        Matrix result(_cols, _rows);
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < _cols; j++) {
                result._data[j][i] = _data[i][j];
            }
        }
        _data = std::move(result._data);
        return *this;
    }
}
