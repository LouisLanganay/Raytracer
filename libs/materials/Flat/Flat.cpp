/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Flat
*/

#include "Flat.hpp"
#include "../../../src/Loader/LibLoader.hpp"
#include <memory>

namespace RayTracer::Materials {
    Flat::Flat()
    {
    }

    Flat::~Flat()
    {
    }

    bool Flat::scatter(const Ray &ray, const RayHit &hit, Scatter &scatter) const
    {
        return false;
    }

    Vector3D Flat::getColor(const Ray &ray, const RayHit &hit) const
    {
        return _color;
    }

    extern "C" std::unique_ptr<IMaterial> getEntryPoint()
    {
        return std::make_unique<RayTracer::Materials::Flat>();
    }

    extern "C" std::unique_ptr<PluginType> getTypePoint()
    {
        return std::make_unique<PluginType>(PluginType::MATERIAL);
    }

    extern "C" std::unique_ptr<std::string> getNamePoint()
    {
        return std::make_unique<std::string>("flat");
    }
}
