/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** DirectionalLight
*/

#include "DirectionalLight.hpp"
#include "../../../src/Loader/LibLoader.hpp"

namespace RayTracer::Lights
{
    DirectionalLight::DirectionalLight()
    {
    }

    Vector3D DirectionalLight::computeLights(
        Vector3D color,
        const Ray &ray,
        const RayHit &hit,
        const std::vector<RayTracer::Primitives::IPrimitive *> &primitives
    ) const
    {
        static constexpr double kShadowBias = 1e-5;
        Vector3D lightDirection;
        lightDirection._x = -_direction._x;
        lightDirection._y = -_direction._y;
        lightDirection._z = -_direction._z;
        lightDirection.normalize();
        double angle = hit.normal.dot(lightDirection);

        double shadowIntensity = 1.0;

        Vector3D newColor = color * _color * (_intensity * 0.01);
        newColor.clamp(0, 255);

        double diffuseIntensity = std::max(0.0, angle) * shadowIntensity;
        Vector3D diffuseColor = newColor * diffuseIntensity;

        return diffuseColor;
    }

    extern "C" std::unique_ptr<ILight> getEntryPoint()
    {
        return std::make_unique<DirectionalLight>();
    }

    extern "C" std::unique_ptr<PluginType> getTypePoint()
    {
        return std::make_unique<PluginType>(PluginType::LIGHT);
    }

    extern "C" std::unique_ptr<std::string> getNamePoint()
    {
        return std::make_unique<std::string>("directional");
    }
}
