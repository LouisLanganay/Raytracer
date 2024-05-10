/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cone
*/

#include "Cone.hpp"
#include <cmath>
#include "../../../src/Loader/LibLoader.hpp"
#include <memory>

namespace RayTracer::Primitives {
    Cone::Cone()
    {
    }

    Cone::~Cone()
    {
    }

    bool Cone::hit(const Ray& ray, RayHit& hit)
    {
        if (!_isCenterSet) {
            Matrix transformation = getTransformationMatrix();
            _center = getOrigin();
            _center._x += transformation(0, 3);
            _center._y += transformation(1, 3);
            _center._z += transformation(2, 3);
            _isCenterSet = true;
        }
        Vector3D oc = ray.getOrigin() - _center;

        double k = getRadius() / getHeight();
        double a = ray.getDirection()._x * ray.getDirection()._x + ray.getDirection()._z * ray.getDirection()._z - k * k * ray.getDirection()._y * ray.getDirection()._y;
        double b = 2 * (oc._x * ray.getDirection()._x + oc._z * ray.getDirection()._z - k * k * oc._y * ray.getDirection()._y);
        double c = oc._x * oc._x + oc._z * oc._z - k * k * oc._y * oc._y;
        double delta = b * b - 4 * a * c;

        if (delta < 0)
            return false;

        double t1 = (-b - sqrt(delta)) / (2 * a);
        double t2 = (-b + sqrt(delta)) / (2 * a);
        double t = (t1 < t2) ? t1 : t2;

        if (t < 0)
            return false;

        double hitY = oc._y + t * ray.getDirection()._y;
        if (hitY < 0 || (getHeight() > 0 && hitY > getHeight()))
            return false;

        hit.distance = t;
        hit.point = ray.getPointAt(hit.distance);
        hit.normal = Vector3D(hit.point._x - _center._x, k * k * (hit.point._y - _center._y), hit.point._z - _center._z);
        hit.normal.normalize();
        return true;
    }

    extern "C" std::unique_ptr<IPrimitive> getEntryPoint()
    {
        return std::make_unique<Cone>();
    }

    extern "C" std::unique_ptr<PluginType> getTypePoint()
    {
        return std::make_unique<PluginType>(PluginType::PRIMITIVE);
    }

    extern "C" std::unique_ptr<std::string> getNamePoint()
    {
        return std::make_unique<std::string>("cone");
    }
}