/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Camera
*/

#include "Camera.hpp"

namespace RayTracer {
    Camera::Camera()
    {
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
}
