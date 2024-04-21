/*
** EPITECH PROJECT, 2024
** bs-rt
** File description:
** Vector3D
*/

#ifndef VECTOR3D_HPP_
#define VECTOR3D_HPP_

class Vector3D {
    public:
        Vector3D();
        ~Vector3D() = default;
        Vector3D(double x, double y, double z);

        Vector3D(const Vector3D& other) = default;

        Vector3D(Vector3D&& other) = default;

        Vector3D& operator=(const Vector3D& other);
        Vector3D& operator=(Vector3D&& other);

        double length() const;
        double dot(const Vector3D& other) const;
        double lengthSquared() const;

        Vector3D operator+(const Vector3D& other) const;
        Vector3D& operator+=(const Vector3D& other);
        Vector3D operator-(const Vector3D& other) const;
        Vector3D& operator-=(const Vector3D& other);
        Vector3D operator*(double scalar) const;
        Vector3D& operator*=(double scalar);
        Vector3D operator/(double scalar) const;
        Vector3D& operator/=(double scalar);

        void normalize();
        Vector3D getNormalized() const;
        Vector3D cross(const Vector3D& other) const;

        double _x;
        double _y;
        double _z;
    protected:
    private:
};

#endif /* !VECTOR3D_HPP_ */
