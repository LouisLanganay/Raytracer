/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Lambertian
*/

#include "Lambertian.hpp"
#include "../../../src/Loader/LibLoader.hpp"
#include <memory>

namespace RayTracer::Materials {
    Lambertian::Lambertian()
    {
    }

    Lambertian::~Lambertian()
    {
    }

    bool Lambertian::scatter(const Ray &ray, const RayHit &hit, Scatter &scatter) const
    {
        auto scatter_direction = hit.normal + Vector3D::random_unit_vector();
        if (scatter_direction.near_zero())
            scatter_direction = hit.normal;
        // scatter.scattered = Ray(hit.p, scatter_direction);
        scatter.reflected = Ray(hit.point, scatter_direction);
        scatter.attenuation = _color;
        return true;
    }

    Vector3D Lambertian::getColor(const Ray &ray, const RayHit &hit) const
    {
        return _color;
    }

    extern "C" std::unique_ptr<IMaterial> getEntryPoint()
    {
        return std::make_unique<RayTracer::Materials::Lambertian>();
    }

    extern "C" std::unique_ptr<PluginType> getTypePoint()
    {
        return std::make_unique<PluginType>(PluginType::MATERIAL);
    }

    extern "C" std::unique_ptr<std::string> getNamePoint()
    {
        return std::make_unique<std::string>("lambertian");
    }
}

// bool Lambertian::scatter(const Ray &r_in, const HitRecord &rec, Color &attenuation, Ray &scattered) const
// {
//     auto scatter_direction = rec.normal + Vector3D::random_unit_vector();
//     if (scatter_direction.near_zero())
//         scatter_direction = rec.normal;
//     scattered = Ray(rec.p, scatter_direction);
//     attenuation = albedo;
//     return true;
// }
