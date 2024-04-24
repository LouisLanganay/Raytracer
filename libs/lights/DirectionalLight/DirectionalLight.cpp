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
        Vector3D surfaceNormal = hit.normal.getNormalized();
        Vector3D toLight = lightDirection.getNormalized();
        Ray shadowRay(hit.point + surfaceNormal * kShadowBias, toLight);
        double shadowIntensity = 1.0;
        for (const auto &primitive : primitives) {
            RayHit shadowHit;
            if (primitive == hit.primitive)
                continue;
            if (primitive->hit(shadowRay, shadowHit)) {
                shadowIntensity = 0.0;
                break;
            }
        }

        double diffuseFactor = std::max(0.0, surfaceNormal.dot(toLight));
        Vector3D diffuseColor = color * (_intensity * 0.01) * diffuseFactor * shadowIntensity;

        Vector3D viewDirection;
        viewDirection._x = -ray._direction.getNormalized()._x;
        viewDirection._y = -ray._direction.getNormalized()._y;
        viewDirection._z = -ray._direction.getNormalized()._z;
        Vector3D halfVector = (toLight + viewDirection).getNormalized();
        double specularFactor = std::pow(std::max(0.0, surfaceNormal.dot(halfVector)), 100);
        Vector3D specularColor = _color * specularFactor * shadowIntensity;

        Vector3D illuminationColor = diffuseColor + specularColor;

        return illuminationColor;
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
