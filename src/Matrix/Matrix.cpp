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
        int rows,
        int cols
    ) : rows(rows),
        cols(cols)
    {
        _data.resize(rows, std::vector<double>(cols, 0.0));
    }

    Matrix::Matrix(
        int rows,
        int cols,
        double initialValue
    ) : rows(rows),
        cols(cols)
    {
        _data.resize(rows, std::vector<double>(cols, initialValue));
    }

    Matrix::~Matrix()
    {
    }

    int Matrix::numRows() const
    {
        return rows;
    }

    int Matrix::numCols() const
    {
        return cols;
    }

    Matrix Matrix::operator+(const Matrix &other)
    {
        if (this->rows != other.rows || this->cols != other.cols) {
            throw std::invalid_argument("Matrix operator+ : Matrices must have the same dimensions.");
        }
        Matrix result(this->rows, this->cols);
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++) {
                result._data[i][j] = this->_data[i][j] + other._data[i][j];
            }
        }
        return result;
    }

    Matrix &Matrix::operator+=(const Matrix &other)
    {
        if (this->rows != other.rows || this->cols != other.cols) {
            throw std::invalid_argument("Matrix operator+= : Matrices must have the same dimensions.");
        }
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++) {
                this->_data[i][j] += other._data[i][j];
            }
        }
        return *this;
    }

    Matrix Matrix::operator-(const Matrix &other) const
    {
        if (this->rows != other.rows || this->cols != other.cols) {
            throw std::invalid_argument("Matrix operator- : Matrices must have the same dimensions.");
        }
        Matrix result(this->rows, this->cols);
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++) {
                result._data[i][j] = this->_data[i][j] - other._data[i][j];
            }
        }
        return result;
    }

    Matrix &Matrix::operator-=(const Matrix &other)
    {
        if (this->rows != other.rows || this->cols != other.cols) {
            throw std::invalid_argument("Matrix operator-= : Matrices must have the same dimensions.");
        }
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++) {
                this->_data[i][j] -= other._data[i][j];
            }
        }
        return *this;
    }

    Matrix Matrix::operator*(const Matrix &other) const
    {
        if (this->cols != other.rows) {
            throw std::invalid_argument("Matrix operator* : Matrices must have the same dimensions.");
        }
        Matrix result(this->rows, other.cols);
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                for (int k = 0; k < this->cols; k++) {
                    result._data[i][j] += this->_data[i][k] * other._data[k][j];
                }
            }
        }
        return result;
    }

    Matrix &Matrix::operator*=(const Matrix &other)
    {
        if (this->cols != other.rows) {
            throw std::invalid_argument("Matrix operator*= : Matrices must have the same dimensions.");
        }
        Matrix result(this->rows, other.cols);
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                for (int k = 0; k < this->cols; k++) {
                    result._data[i][j] += this->_data[i][k] * other._data[k][j];
                }
            }
        }
        this->_data = std::move(result._data);
        this->cols = other.cols;
        return *this;
    }

    Matrix Matrix::operator*(double scalar) const
    {
        Matrix result(this->rows, this->cols);
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++) {
                result._data[i][j] = this->_data[i][j] * scalar;
            }
        }
        return result;
    }

    Matrix &Matrix::operator*=(double scalar)
    {
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++) {
                this->_data[i][j] *= scalar;
            }
        }
        return *this;
    }

    Matrix Matrix::operator/(double scalar) const
    {
        if (scalar == 0) {
            throw std::invalid_argument("Matrix operator/ : Scalar must not be 0.");
        }
        Matrix result(this->rows, this->cols);
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++) {
                result._data[i][j] = this->_data[i][j] / scalar;
            }
        }
        return result;
    }

    Matrix &Matrix::operator/=(double scalar)
    {
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++) {
                this->_data[i][j] /= scalar;
            }
        }
        return *this;
    }

    Matrix &Matrix::operator=(const Matrix &other)
    {
        if (this != &other) {
            this->rows = other.rows;
            this->cols = other.cols;

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    this->_data[i][j] = other._data[i][j];
                }
            }
        }
        return *this;
    }

    Matrix &Matrix::operator=(Matrix &&other)
    {
        if (this != &other) {
            this->rows = other.rows;
            this->cols = other.cols;
            this->_data = std::move(other._data);
        }
        return *this;
    }

    Vector3D Matrix::operator*(const Vector3D &vector) const
    {
        if (this->cols != 3) {
            throw std::invalid_argument("Matrix operator* : Matrix must have 3 columns.");
        }
        Vector3D result;
        result._x = this->_data[0][0] * vector._x + this->_data[0][1] * vector._y + this->_data[0][2] * vector._z;
        result._y = this->_data[1][0] * vector._x + this->_data[1][1] * vector._y + this->_data[1][2] * vector._z;
        result._z = this->_data[2][0] * vector._x + this->_data[2][1] * vector._y + this->_data[2][2] * vector._z;
        return result;
    }

    Point3D Matrix::operator*(const Point3D &point) const
    {
        if (this->cols != 4) {
            throw std::invalid_argument("Matrix operator* : Matrix must have 4 columns.");
        }
        Point3D result;
        result._x = this->_data[0][0] * point._x + this->_data[0][1] * point._y + this->_data[0][2] * point._z + this->_data[0][3];
        result._y = this->_data[1][0] * point._x + this->_data[1][1] * point._y + this->_data[1][2] * point._z + this->_data[1][3];
        result._z = this->_data[2][0] * point._x + this->_data[2][1] * point._y + this->_data[2][2] * point._z + this->_data[2][3];
        return result;
    }

    double &Matrix::operator()(int row, int col)
    {
        if (row < 0 || row >= this->rows || col < 0 || col >= this->cols) {
            throw std::invalid_argument("Matrix operator() : Index out of bounds.");
        }
        return this->_data[row][col];
    }
}
