/*
** EPITECH PROJECT, 2024
** bs-rt
** File description:
** Rectangle3D
*/

#ifndef RECTANGLE3D_HPP_
#define RECTANGLE3D_HPP_

#include "../Point/Point3D.hpp"
#include "../Ray/Ray.hpp"

class Rectangle3D {
    public:
        Rectangle3D() = default;
        ~Rectangle3D() = default;

        Rectangle3D(
            const Point3D& origin,
            const Vector3D& bottom_side,
            const Vector3D& left_side
        );

        Point3D pointAt(double u, double v) const;

        Point3D _origin;
        Vector3D _bottom_side;
        Vector3D _right_side;
    protected:
    private:
};

#endif /* !RECTANGLE3D_HPP_ */
