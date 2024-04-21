/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Camera
*/

#include "Camera.hpp"

namespace RayTracer {
    Camera::Camera(
        Point3D origin,
        Point3D resolution
    ) : _origin(origin),
        _resolution(resolution)
    {
        _screen = Rectangle3D(
            Point3D(_origin._x, _origin._y, 200),
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
        Point3D screenPoint = _screen.pointAt(u, v);
        Vector3D direction = (screenPoint - _origin).getNormalized();

        return Ray(_origin, direction);
    }
}
