/*
** EPITECH PROJECT, 2024
** bs-rt
** File description:
** Ray
*/

#include "Ray.hpp"

Ray::Ray(
    const Point3D& origin,
    const Vector3D& direction
) : _origin(origin),
    _direction(direction)
{
}

Ray::Ray(
    const Ray& other
) : _origin(other._origin),
    _direction(other._direction)
{
}

Ray::Ray(
    Ray&& other
) : _origin(other._origin),
    _direction(other._direction)
{
}

Ray& Ray::operator=(const Ray& other)
{
    _origin = other._origin;
    _direction = other._direction;
    return *this;
}

Ray& Ray::operator=(Ray&& other)
{
    _origin = other._origin;
    _direction = other._direction;
    return *this;
}

Point3D Ray::getPointAt(double distance) const
{
    return _origin + _direction * distance;
}
