/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Mirror
*/

#include "Mirror.hpp"
#include "../../../src/Loader/LibLoader.hpp"
#include <memory>

namespace RayTracer::Materials {
    Mirror::Mirror()
    {
    }

    Mirror::~Mirror()
    {
    }

    bool Mirror::scatter(const Ray &ray, const RayHit &hit, Scatter &scatter) const
    {
        return false;
    }

    Vector3D Mirror::getColor(const Ray &ray, const RayHit &hit) const
    {
        return _color;
    }

    extern "C" std::unique_ptr<IMaterial> getEntryPoint()
    {
        return std::make_unique<RayTracer::Materials::Mirror>();
    }

    extern "C" std::unique_ptr<PluginType> getTypePoint()
    {
        return std::make_unique<PluginType>(PluginType::MATERIAL);
    }

    extern "C" std::unique_ptr<std::string> getNamePoint()
    {
        return std::make_unique<std::string>("mirror");
    }
}
