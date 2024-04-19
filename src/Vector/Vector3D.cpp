/*
** EPITECH PROJECT, 2024
** bs-rt
** File description:
** Vector3D
*/

#include "Vector3D.hpp"
#include <cmath>

Vector3D::Vector3D() : _x(0), _y(0), _z(0)
{
}

Vector3D::Vector3D(
    double x,
    double y,
    double z
) : _x(x),
    _y(y),
    _z(z)
{
}

double Vector3D::length() const
{
    return sqrt(_x * _x + _y * _y + _z * _z);
}

double Vector3D::dot(const Vector3D& other) const
{
    return _x * other._x + _y * other._y + _z * other._z;
}

Vector3D Vector3D::operator+(const Vector3D& other) const
{
    return Vector3D(_x + other._x, _y + other._y, _z + other._z);
}

Vector3D& Vector3D::operator+=(const Vector3D& other)
{
    _x += other._x;
    _y += other._y;
    _z += other._z;
    return *this;
}

Vector3D Vector3D::operator-(const Vector3D& other) const
{
    return Vector3D(_x - other._x, _y - other._y, _z - other._z);
}

Vector3D& Vector3D::operator-=(const Vector3D& other)
{
    _x -= other._x;
    _y -= other._y;
    _z -= other._z;
    return *this;
}

Vector3D Vector3D::operator*(double scalar) const
{
    return Vector3D(_x * scalar, _y * scalar, _z * scalar);
}

Vector3D& Vector3D::operator*=(double scalar)
{
    _x *= scalar;
    _y *= scalar;
    _z *= scalar;
    return *this;
}

Vector3D Vector3D::operator/(double scalar) const
{
    return Vector3D(_x / scalar, _y / scalar, _z / scalar);
}

Vector3D& Vector3D::operator/=(double scalar)
{
    _x /= scalar;
    _y /= scalar;
    _z /= scalar;
    return *this;
}

void Vector3D::normalize()
{
    double len = length();

    if (len != 0) {
        _x /= len;
        _y /= len;
        _z /= len;
    }
}
