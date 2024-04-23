/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** AmbientLight
*/

#include "AmbientLight.hpp"
#include "../../../src/Loader/LibLoader.hpp"
#include <memory>

namespace RayTracer::Lights {
    AmbientLight::AmbientLight()
    {
    }

    AmbientLight::~AmbientLight()
    {
    }

    extern "C" std::unique_ptr<ILight> getEntryPoint()
    {
        return std::make_unique<AmbientLight>();
    }

    extern "C" std::unique_ptr<PluginType> getTypePoint()
    {
        return std::make_unique<PluginType>(PluginType::LIGHT);
    }

    extern "C" std::unique_ptr<std::string> getNamePoint()
    {
        return std::make_unique<std::string>("ambient");
    }
}

