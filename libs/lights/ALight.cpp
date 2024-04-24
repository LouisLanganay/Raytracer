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
        _color = Vector3D(x, y, z);
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

    Vector3D ALight::getColor() const
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
}
