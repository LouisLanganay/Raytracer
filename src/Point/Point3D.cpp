/*
** EPITECH PROJECT, 2024
** bs-rt
** File description:
** Point3D
*/

#include "Point3D.hpp"
#include "../Vector/Vector3D.hpp"
#include <cmath>

Point3D::Point3D(
    double x,
    double y,
    double z
) : _x(x),
    _y(y),
    _z(z)
{
}

Point3D::Point3D(
    const Vector3D& vec
) : _x(vec._x),
    _y(vec._y),
    _z(vec._z)
{
}

Point3D Point3D::operator+(Point3D& other) const
{
    return Point3D(_x + other._x, _y + other._y, _z + other._z);
}

Point3D Point3D::operator+(const Point3D& other) const
{
    return Point3D(_x + other._x, _y + other._y, _z + other._z);
}

Point3D Point3D::operator+(const Vector3D& vec) const
{
    return Point3D(_x + vec._x, _y + vec._y, _z + vec._z);
}

Point3D Point3D::operator-(const Vector3D& vec) const
{
    return Point3D(_x - vec._x, _y - vec._y, _z - vec._z);
}

Point3D Point3D::operator-(const Point3D& other) const
{
    return Point3D(_x - other._x, _y - other._y, _z - other._z);
}

Point3D& Point3D::operator=(const Point3D& other)
{
    _x = other._x;
    _y = other._y;
    _z = other._z;
    return *this;
}

Vector3D Point3D::operator=(const Point3D& other) const
{
    return Vector3D(_x - other._x, _y - other._y, _z - other._z);
}

Point3D& Point3D::operator+=(const Vector3D& vec)
{
    _x += vec._x;
    _y += vec._y;
    _z += vec._z;
    return *this;
}

double Point3D::length() const
{
    return sqrt(_x * _x + _y * _y + _z * _z);
}
