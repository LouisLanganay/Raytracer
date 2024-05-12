/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Matrix
*/

#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#include <vector>
#include "../Point/Point3D.hpp"

class Vector3D;

namespace RayTracer {
    class Matrix {
        public:
            Matrix();
            Matrix(int rows, int cols);
            Matrix(int rows, int cols, double initialValue);
            ~Matrix();

            int numRows() const;
            int numCols() const;

            Matrix(const Matrix& other) = default;
            Matrix(Matrix&& other) = default;

            double &operator()(int row, int col);


            Matrix operator+(const Matrix &other);

            Matrix &operator+=(const Matrix &other);

            Matrix operator-(const Matrix &other) const;
            Matrix &operator-=(const Matrix &other);
            Matrix operator*(const Matrix &other) const;
            Matrix &operator*=(const Matrix &other);

            Matrix operator*(double scalar) const;
            Matrix &operator*=(double scalar);
            Matrix operator/(double scalar) const;
            Matrix &operator/=(double scalar);

            Point3D operator*(const Point3D &point) const;
            Vector3D operator*(const Vector3D &vector) const;

            Matrix &operator=(const Matrix &other);
            Matrix &operator=(Matrix &&other);

            Matrix inverse();
            Matrix transpose();

        protected:
            std::vector<std::vector<double>> _data;
            int _rows;
            int _cols;

    };
}

#endif /* !MATRIX_HPP_ */
