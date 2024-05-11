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
    return std::sqrt(dot(*this));
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
    *this /= length();
}

Vector3D Vector3D::getNormalized() const
{
    double magnitude = sqrt(_x * _x + _y * _y + _z * _z);
    if (magnitude != 0.0) {
        return Vector3D(_x / magnitude, _y / magnitude, _z / magnitude);
    }
    return Vector3D();
}

Vector3D& Vector3D::operator=(const Vector3D& other)
{
    _x = other._x;
    _y = other._y;
    _z = other._z;
    return *this;
}

Vector3D& Vector3D::operator=(Vector3D&& other)
{
    _x = other._x;
    _y = other._y;
    _z = other._z;
    return *this;
}

Vector3D Vector3D::cross(const Vector3D& other) const
{
    return {
        _y * other._z - _z * other._y,
        _z * other._x - _x * other._z,
        _x * other._y - _y * other._x
    };
}

double Vector3D::lengthSquared() const
{
    return dot(*this);
}

Vector3D Vector3D::operator*(const Vector3D& other) const
{
    return Vector3D(_x * other._x, _y * other._y, _z * other._z);
}

void Vector3D::clamp(double min, double max)
{
    _x = std::min(std::max(_x, min), max);
    _y = std::min(std::max(_y, min), max);
    _z = std::min(std::max(_z, min), max);
}

Vector3D Vector3D::operator-() const
{
    return Vector3D(-_x, -_y, -_z);
}

double Vector3D::random_double()
{
    return rand() / (RAND_MAX + 1.0);
}

double Vector3D::random_double(double min, double max)
{
    return min + (max - min) * random_double();
}

Vector3D Vector3D::random()
{
    return Vector3D(random_double(), random_double(), random_double());
}

Vector3D Vector3D::random(double min, double max)
{
    return Vector3D(random_double(min, max), random_double(min, max), random_double(min, max));
}

Vector3D Vector3D::random_unit_vector()
{
    return unit_vector(random());
}

Vector3D Vector3D::unit_vector()
{
    return unit_vector(*this);
}

Vector3D Vector3D::unit_vector(const Vector3D& vec)
{
    return vec / vec.length();
}

Vector3D operator*(double scalar, const Vector3D& vec)
{
    return vec * scalar;
}

bool Vector3D::near_zero() const
{
    const auto s = 1e-8;
    return (fabs(_x) < s) && (fabs(_y) < s) && (fabs(_z) < s);
}

double Vector3D::getX() const
{
    return _x;
}

double Vector3D::getY() const
{
    return _y;
}

double Vector3D::getZ() const
{
    return _z;
}
