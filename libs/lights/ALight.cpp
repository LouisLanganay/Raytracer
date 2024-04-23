/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** ALight
*/

#include "ALight.hpp"

namespace RayTracer::Lights {

    void ALight::setOrigin(double x, double y, double z)
    {
        _origin = Point3D(x, y, z);
    }

    void ALight::setColor(double x, double y, double z)
    {
        _color = Point3D(x, y, z);
    }

    void ALight::setType(const std::string &type)
    {
        _type = type;
    }

    void ALight::setIntensity(double intensity)
    {
        _intensity = intensity;
    }

    void ALight::setPosition(double x, double y, double z)
    {
        _position = Point3D(x, y, z);
    }

    Point3D ALight::getOrigin() const
    {
        return _origin;
    }

    Point3D ALight::getColor() const
    {
        return _color;
    }

    Point3D ALight::getPosition() const
    {
        return _position;
    }

    std::string ALight::getType() const
    {
        return _type;
    }

    double ALight::getIntensity() const
    {
        return _intensity;
    }

    bool ALight::computeLights(const Point3D &point,
        const Vector3D &normal,
        Point3D &color,
        double &intensity,
        const std::vector<RayTracer::Primitives::IPrimitive *> &primitives,
        Primitives::IPrimitive *currentPrimitive)
    {
        return false;
    }
}
