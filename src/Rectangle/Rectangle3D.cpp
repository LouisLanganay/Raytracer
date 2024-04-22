/*
** EPITECH PROJECT, 2024
** bs-rt
** File description:
** Rectangle3D
*/

#include "Rectangle3D.hpp"

Rectangle3D::Rectangle3D(
    const Point3D& origin,
    const Vector3D& bottom_side,
    const Vector3D& left_side
) : _origin(origin),
    _bottom_side(bottom_side),
    _right_side(left_side)
{
}

Point3D Rectangle3D::pointAt(double u, double v) const
{
    return _origin + _bottom_side * u + _right_side * v;
}
