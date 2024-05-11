/*
** EPITECH PROJECT, 2024
** bs-rt
** File description:
** Ray
*/

#ifndef RAY_HPP_
#define RAY_HPP_

#include "../Point/Point3D.hpp"
#include "../Vector/Vector3D.hpp"

class Ray {
    public:
        Ray() = default;
        ~Ray() = default;

        Ray(const Point3D& origin, const Vector3D& direction);
        Ray(const Ray& other);
        Ray(Ray&& other);

        Ray& operator=(const Ray& other);
        Ray& operator=(Ray&& other);

        Point3D getPointAt(double distance) const;
        Point3D getOrigin() const;
        Vector3D getDirection() const;

        static double dot(const Vector3D &u, const Vector3D &v);

        Point3D _origin;
        Vector3D _direction;
    protected:
    private:
};

#endif /* !RAY_HPP_ */
