/*
** EPITECH PROJECT, 2024
** bs-rt
** File description:
** Vector3D
*/

#ifndef VECTOR3D_HPP_
#define VECTOR3D_HPP_

class Point3D;

class Vector3D {
    public:
        Vector3D();
        ~Vector3D() = default;
        Vector3D(double x, double y, double z);
        Vector3D(const Point3D& other);

        Vector3D(const Vector3D& other) = default;

        Vector3D(Vector3D&& other) = default;

        Vector3D& operator=(const Vector3D& other);
        Vector3D& operator=(Vector3D&& other);

        double length() const;
        double dot(const Vector3D& other) const;
        double lengthSquared() const;

        Vector3D operator==(const Vector3D& other) const;
        Vector3D operator+(const Vector3D& other) const;
        Vector3D operator+(const Point3D& point) const;
        Vector3D& operator+=(const Vector3D& other);
        Vector3D operator-(const Vector3D& other) const;
        Vector3D operator-(const Point3D& other) const;
        Vector3D& operator-=(const Vector3D& other);
        Vector3D operator*(double scalar) const;
        Vector3D& operator*=(double scalar);
        Vector3D &operator*=(const Vector3D &other);
        Vector3D operator/(double scalar) const;
        Vector3D& operator/=(double scalar);
        Vector3D operator*(const Vector3D& other) const;
        Vector3D operator-() const;

        void normalize();
        bool isZero() const;
        Vector3D getNormalized() const;
        Vector3D cross(const Vector3D& other) const;
        void clamp(double min, double max);

        double _x;
        double _y;
        double _z;
    protected:
    private:
};

#include "../Point/Point3D.hpp"

#endif /* !VECTOR3D_HPP_ */
