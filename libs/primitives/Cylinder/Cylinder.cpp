/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cylinder
*/

#include "Cylinder.hpp"
#include <cmath>
#include "../../../src/Loader/LibLoader.hpp"
#include <memory>

namespace RayTracer::Primitives {
    Cylinder::Cylinder()
    {
    }

    Cylinder::~Cylinder()
    {
    }

bool Cylinder::hit(const Ray &ray, RayHit &hit)
{
    Vector3D oc = ray.getOrigin() - _center;

    float a = ray.getDirection()._x * ray.getDirection()._x + ray.getDirection()._z * ray.getDirection()._z;
    float b = 2 * (oc._x * ray.getDirection()._x + oc._z * ray.getDirection()._z);
    float c = oc._x * oc._x + oc._z * oc._z - _radius * _radius;
    float delta = b * b - 4 * a * c;

    if (delta < 0)
        return false;

    float t1 = (-b - sqrt(delta)) / (2 * a);
    float t2 = (-b + sqrt(delta)) / (2 * a);

    float t_hit = std::min(t1, t2);
    if (t_hit > 0) {
        hit.point = ray.getPointAt(t_hit);
        if (hit.point._y >= _center._y && hit.point._y <= _center._y + _height) {
            hit.distance = t_hit;
            // Remove the next line as hit.point is already assigned to hit_point
            // hit.point = hit_point;
            hit.normal = Vector3D(hit.point._x - _center._x, 0, hit.point._z - _center._z);
            hit.normal.normalize();
            return true;
        }
    }
    return false;
}



    extern "C" std::unique_ptr<IPrimitive> getEntryPoint()
    {
        return std::make_unique<Cylinder>();
    }

    extern "C" std::unique_ptr<PluginType> getTypePoint()
    {
        return std::make_unique<PluginType>(PluginType::PRIMITIVE);
    }

    extern "C" std::unique_ptr<std::string> getNamePoint()
    {
        return std::make_unique<std::string>("cylinder");
    }
}