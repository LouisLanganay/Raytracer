/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** APrimitive
*/

#include "APrimitive.hpp"

namespace RayTracer::Primitives {
    void APrimitive::setType(const std::string &type)
    {
        _type = type;
    }

    void APrimitive::setOrigin(int x, int y, int z)
    {
        _origin = Point3D(x, y, z);
    }

    void APrimitive::setRotation(int x, int y, int z)
    {
        _rotation = Point3D(x, y, z);
    }

    void APrimitive::setRadius(double radius)
    {
        _radius = radius;
    }

    void APrimitive::setAxis(RayTracer::Primitives::Axis axis)
    {
        _axis = axis;
    }

    std::string APrimitive::getType() const
    {
        return _type;
    }

    Point3D APrimitive::getOrigin() const
    {
        return _origin;
    }

    Point3D APrimitive::getRotation() const
    {
        return _rotation;
    }

    double APrimitive::getRadius() const
    {
        return _radius;
    }

    RayTracer::Primitives::Axis APrimitive::getAxis() const
    {
        return _axis;
    }

    std::shared_ptr<RayTracer::Materials::IMaterial> APrimitive::getMaterial() const
    {
        return _material;
    }

    void APrimitive::setMaterial(const std::shared_ptr<RayTracer::Materials::IMaterial> &material)
    {
        _material = material;
    }
}
