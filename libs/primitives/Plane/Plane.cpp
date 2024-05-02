/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Plane
*/


#include "Plane.hpp"
#include "../../../src/Loader/LibLoader.hpp"
#include <memory>
#include <cmath>
#include <Vector3D.hpp>

namespace RayTracer::Primitives {
    Plane::Plane()
    {
    }

    Plane::~Plane()
    {
    }

    bool Plane::hit(const Ray& ray, RayHit& hit)
    {
        const double EPSILON = 1e-6;
        hit.normal._x = ray._origin._x * ray._direction._x;
        hit.normal._y = ray._origin._y * ray._direction._y;
        hit.normal._z = ray._origin._z * ray._direction._z;



        double denominator = ray.getDirection().dot(hit.normal);
        if (fabs(denominator) < EPSILON)
            return false; // Ray is parallel to the plane

        double t = (hit.point - ray.getOrigin()).dot(hit.normal) / denominator;

        if (t <= EPSILON)
            return false; // Intersection behind the ray origin

        hit.distance = t;
        hit.point = ray.getPointAt(t);

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
