/*
** EPITECH PROJECT, 2024
** bs-rt
** File description:
** Point3D
*/

#ifndef POINT3D_HPP_
#define POINT3D_HPP_

#include "../Vector/Vector3D.hpp"

class Point3D {
    public:
        Point3D() = default;
        ~Point3D() = default;

        Point3D(double x, double y, double z);

        Point3D(const Point3D& other) = default;
        Point3D(Point3D&& other) = default;

        Point3D& operator=(const Point3D& other) = default;
        Point3D& operator=(Point3D&& other) = default;
        Point3D operator+(const Vector3D& vec) const;
        Vector3D operator-(const Point3D& other) const;
        Point3D operator-(const Vector3D& vec) const;

        double _x;
        double _y;
        double _z;
    protected:
    private:
};

#endif /* !POINT3D_HPP_ */
