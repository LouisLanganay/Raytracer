/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Sphere
*/

#include "Sphere.hpp"
#include "../../../src/Loader/LibLoader.hpp"
#include <memory>

namespace RayTracer::Primitives {
    Sphere::Sphere()
    {
    }

    Sphere::~Sphere()
    {
    }

    bool Sphere::hit(const Ray& ray, RayHit& hit) const
    {
        Vector3D oc = ray._origin - _origin;
        double a = ray._direction.dot(ray._direction);
        double b = 2.0 * oc.dot(ray._direction);
        double c = oc.dot(oc) - _radius * _radius;
        double discriminant = b * b - 4 * a * c;
        if (discriminant < 0)
            return false;
        if (discriminant == 0) {
            hit.distance = -b / a;
            hit.point = ray.getPointAt(hit.distance);
            hit.normal = Vector3D(hit.point - _origin) / _radius;
        } else {
            auto temp = (-b - sqrt(discriminant)) / a;
            if (temp > 0) {
                hit.distance = temp;
                hit.point = ray.getPointAt(hit.distance);
                hit.normal = Vector3D(hit.point - _origin) / _radius;
            } else {
                temp = (-b + sqrt(discriminant)) / a;
                hit.distance = temp;
                hit.point = ray.getPointAt(hit.distance);
                hit.normal = Vector3D(hit.point - _origin) / _radius;
            }
        }
        hit.normal.normalize();
        return true;
    }

    extern "C" std::unique_ptr<IPrimitive> getEntryPoint()
    {
        return std::make_unique<Sphere>();
    }

    extern "C" std::unique_ptr<PluginType> getTypePoint()
    {
        return std::make_unique<PluginType>(PluginType::PRIMITIVE);
    }

    extern "C" std::unique_ptr<std::string> getNamePoint()
    {
        return std::make_unique<std::string>("sphere");
    }
}
