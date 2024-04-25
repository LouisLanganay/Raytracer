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
        Vector3D lightDir = _position - hit.point;
        Vector3D shadowDir = hit.point - _position;
        Ray shadowRay(_position, shadowDir.getNormalized());
        double angle = hit.normal.dot(lightDir);

        for (const auto &primitive : primitives) {
            RayHit shadowHit;
            if (primitive == hit.primitive)
                continue;
            if (primitive->hit(shadowRay, shadowHit) && shadowHit.distance < lightDir.length()) {
                return Vector3D(0, 0, 0);
            }
        }

        double shadowIntensity = 1.0;

        Vector3D newColor = color * _color * (_intensity * 0.01);
        newColor.clamp(0, 255);

        double diffuseIntensity = std::max(0.0, angle) * shadowIntensity;
        Vector3D diffuseColor = newColor * diffuseIntensity;

        return diffuseColor;
    }

    Vector3D PointLight::computeShadowIntensity(
        Vector3D color,
        const Ray &ray,
        const RayHit &hit,
        const std::vector<RayTracer::Primitives::IPrimitive *> &primitives
    ) const
    {
        static constexpr double kShadowBias = 1e-5;
        Vector3D lightDir = _position - hit.point;
        Vector3D shadowDir = hit.point - _position;
        Ray shadowRay(_position, shadowDir.getNormalized());
        double angle = hit.normal.dot(lightDir);

        for (const auto &primitive : primitives) {
            RayHit shadowHit;
            if (primitive == hit.primitive)
                continue;
            if (primitive->hit(shadowRay, shadowHit) && shadowHit.distance < lightDir.length()) {
                return Vector3D(0, 0, 0);
            }
        }

        double shadowIntensity = 1.0;

        Vector3D newColor = color * _color * (_intensity * 0.01);
        newColor.clamp(0, 255);

        double diffuseIntensity = std::max(0.0, angle) * shadowIntensity;
        Vector3D diffuseColor = newColor * diffuseIntensity;

        return diffuseColor;
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
