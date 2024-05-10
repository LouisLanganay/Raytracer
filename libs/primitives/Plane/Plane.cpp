/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cylinder
*/

#include "Plane.hpp"
#include <cmath>
#include "../../../src/Loader/LibLoader.hpp"
#include <memory>

namespace RayTracer::Primitives {
    Plane::Plane()
    {
    }

    Plane::~Plane()
    {
    }

    bool Plane::hit(const Ray &ray, RayHit &hit)
    {
        constexpr double EPSILON = 0.000001;

        if (!_isNormalSet) {
            Axis axis = getAxis();
            switch (axis)
            {
            case Axis::X:
                _normal = Vector3D(1, 0, 0);
                break;
            case Axis::Y:
                _normal = Vector3D(0, 1, 0);
                break;
            case Axis::Z:
                _normal = Vector3D(0, 0, 1);
                break;
            default:
                throw std::runtime_error("Invalid axis");
                break;
            }
            Matrix transformation = getTransformationMatrix();
            _center = getOrigin();
            _center._x += transformation(0, 3);
            _center._y += transformation(1, 3);
            _center._z += transformation(2, 3);
            _center = _center;
            _isNormalSet = true;
        }
        double denominator = _normal.dot(ray.getDirection());
        if (fabs(denominator) < EPSILON)
            return false;

        double t = (_center - ray.getOrigin()).dot(_normal) / denominator;

        if (t < 0)
            return false;

        hit.distance = t;
        hit.point = ray.getPointAt(hit.distance);
        hit.normal = Vector3D(_normal);
        hit.normal.normalize();
        return true;
    }

    extern "C" std::unique_ptr<IPrimitive> getEntryPoint()
    {
        return std::make_unique<Plane>();
    }

    extern "C" std::unique_ptr<PluginType> getTypePoint()
    {
        return std::make_unique<PluginType>(PluginType::PRIMITIVE);
    }

    extern "C" std::unique_ptr<std::string> getNamePoint()
    {
        return std::make_unique<std::string>("plane");
    }

}