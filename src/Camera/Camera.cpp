/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Camera
*/

#include "Camera.hpp"
#include <iostream>

namespace RayTracer {
    Camera::Camera(
        Point3D origin,
        Point3D resolution
    ) : _origin(origin),
        _resolution(resolution)
    {
        _screen = Rectangle3D(
            Point3D(_origin._x - resolution._x / 2, _origin._y - resolution._y / 2, 0),
            Vector3D(resolution._x, 0, 0),
            Vector3D(0, resolution._y, 0)
        );
    }

    void Camera::setResolution(int x, int y)
    {
        _resolution = Point3D(x, y, 0);
    }

    void Camera::setFov(double fov)
    {
        _fov = fov;
    }

    void Camera::setOrigin(double x, double y, double z)
    {
        _origin = Point3D(x, y, z);
    }

    void Camera::setRotation(double x, double y, double z)
    {
        _rotation = Point3D(x, y, z);
    }

    Point3D Camera::getResolution() const
    {
        return _resolution;
    }

    Point3D Camera::getOrigin() const
    {
        return _origin;
    }

    Point3D Camera::getRotation() const
    {
        return _rotation;
    }

    double Camera::getFov() const
    {
        return _fov;
    }

    Ray Camera::generateRay(double u, double v) const
    {
        Vector3D direction = (_screen.pointAt(u, v) - _origin);
        return Ray(_origin, direction);
    }

    void Camera::moveCamera(double x, double y, double z)
    {
        _origin._x += x;
        _origin._y += y;
        _origin._z += z;
    }

    void Camera::rotateCamera(double x, double y, double z)
    {
        _rotation._x += x;
        _rotation._y += y;
        _rotation._z += z;
    }
}
