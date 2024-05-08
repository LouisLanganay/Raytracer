/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** PointLight
*/

#include "PointLight.hpp"
#include "../../../src/Loader/LibLoader.hpp"

namespace RayTracer::Lights
{
    PointLight::PointLight()
    {
    }

    Vector3D PointLight::computeLights(
        Vector3D color,
        const Ray &ray,
        const RayHit &hit,
        const std::vector<RayTracer::Primitives::IPrimitive *> &primitives
    ) const
    {
        static constexpr double kShadowBias = 1e-5;

        // Compute direction from hit point to the light position
        Vector3D lightDirection = (_origin - hit.point);
        lightDirection.normalize();

        // Calculate angle between light direction and surface normal
        double angle = hit.normal.dot(lightDirection);

        // Compute distance from hit point to light position
        Vector3D dist = (_origin - hit.point);
        double distanceToLight = dist.length();

        // Compute shadow intensity
        double shadowIntensity = 1.0;

        // Calculate attenuation based on distance (inverse square law)
        double attenuation = 1.0 / (1.0 + _attenuation * distanceToLight + _attenuation * _attenuation * distanceToLight * distanceToLight);

        // Compute light intensity taking into account attenuation
        double lightIntensity = _intensity * attenuation * 0.01;

        // Compute diffuse color
        Vector3D newColor = color * _color;
        newColor.clamp(0, 255);

        double diffuseIntensity = std::max(0.0, angle) * shadowIntensity;
        Vector3D diffuseColor = newColor * diffuseIntensity;

        return diffuseColor * lightIntensity;

    }

    extern "C" std::unique_ptr<ILight> getEntryPoint()
    {
        return std::make_unique<PointLight>();
    }

    extern "C" std::unique_ptr<PluginType> getTypePoint()
    {
        return std::make_unique<PluginType>(PluginType::LIGHT);
    }

    extern "C" std::unique_ptr<std::string> getNamePoint()
    {
        return std::make_unique<std::string>("point");
    }
}
