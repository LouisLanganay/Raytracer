/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** APrimitive
*/

#include "APrimitive.hpp"

namespace RayTracer::Primitives {
    APrimitive::APrimitive () : _translation(4, 4, 1), _rotation(4, 4, 1), _scale(4, 4, 1)
    {
    }

    void APrimitive::setType(const std::string &type)
    {
        _type = type;
    }

    void APrimitive::setOrigin(double x, double y, double z)
    {
        _origin = Point3D(x, y, z);
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

    Matrix APrimitive::getRotation() const
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

    double APrimitive::getHeight() const
    {
        return _height;
    }

    double APrimitive::getWidth() const
    {
        return _width;
    }

    void APrimitive::setHeight(double height)
    {
        _height = height;
    }

    void APrimitive::setWidth(double width)
    {
        _width = width;
    }

    void APrimitive::setTranslation(const Vector3D &translation)
    {
        printf("set translation\n");
        _translation(0, 3) = translation._x;
        _translation(1, 3) = translation._y;
        _translation(2, 3) = translation._z;
    }

    void APrimitive::setRotation(const Vector3D &rotation)
    {
        _rotation(0, 0) = cos(rotation._y) * cos(rotation._z);
        _rotation(0, 1) = -cos(rotation._y) * sin(rotation._z);
        _rotation(0, 2) = sin(rotation._y);
        _rotation(1, 0) = cos(rotation._x) * sin(rotation._z) + sin(rotation._x) * sin(rotation._y) * cos(rotation._z);
        _rotation(1, 1) = cos(rotation._x) * cos(rotation._z) - sin(rotation._x) * sin(rotation._y) * sin(rotation._z);
        _rotation(1, 2) = -sin(rotation._x) * cos(rotation._y);
        _rotation(2, 0) = sin(rotation._x) * sin(rotation._z) - cos(rotation._x) * sin(rotation._y) * cos(rotation._z);
        _rotation(2, 1) = sin(rotation._x) * cos(rotation._z) + cos(rotation._x) * sin(rotation._y) * sin(rotation._z);
        _rotation(2, 2) = cos(rotation._x) * cos(rotation._y);
    }

    void APrimitive::setScale(const Vector3D &scale)
    {
        _scale(0, 0) = scale._x;
        _scale(1, 1) = scale._y;
        _scale(2, 2) = scale._z;
    }

    Matrix APrimitive::getTransformationMatrix() const
    {
        return _translation * _rotation * _scale;
    }
}
