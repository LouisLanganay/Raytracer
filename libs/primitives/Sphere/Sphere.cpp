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

    bool Sphere::hit(const Ray& r, Interval interval, HitRecord& rec)
    {
        Vector3D oc = r.getOrigin() - _center;
        double a = r.getDirection().lengthSquared();
        double b = Ray::dot(oc, r.getDirection());
        double c = oc.lengthSquared() - _radius * _radius;
        double discriminant = b * b - a * c;
        if (discriminant < 0)
            return false;
        double sqrtd = sqrt(discriminant);
        double root = (-b - sqrtd) / a;
        if (root < interval.min() || interval.max() < root) {
            root = (-b + sqrtd) / a;
            if (root < interval.min() || interval.max() < root)
                return false;
        }
        rec.t = root;
        rec.p = r.getPointAt(rec.t);
        
        Vector3D outward_normal = (rec.p - _center) / _radius;
        rec.set_face_normal(r, outward_normal);
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
