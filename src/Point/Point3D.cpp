/*
** EPITECH PROJECT, 2024
** bs-rt
** File description:
** Point3D
*/

#include "Point3D.hpp"

Point3D::Point3D(
    double x,
    double y,
    double z
) : _x(x),
    _y(y),
    _z(z)
{
}

Point3D Point3D::operator+(const Vector3D& vec) const
{
    return Point3D(_x + vec._x, _y + vec._y, _z + vec._z);
}

Vector3D Point3D::operator-(const Point3D& other) const
{
    return Vector3D(_x - other._x, _y - other._y, _z - other._z);
}
