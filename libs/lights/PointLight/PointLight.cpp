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
        Vector3D lightDir = _position - hit.point;
        double distance = lightDir.length();
        lightDir.normalize();
        double angle = hit.normal.dot(lightDir);

        Vector3D shadowIntensity = computeShadowIntensity(color, ray, hit, primitives);

        return shadowIntensity;
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
        double distance = lightDir.length();
        lightDir.normalize();
        double angle = hit.normal.dot(lightDir);

        Ray shadowRay(hit.point + hit.normal * kShadowBias, lightDir);
        RayHit tmp;
        tmp.distance = std::numeric_limits<double>::max();
        for (Primitives::IPrimitive *primitive: primitives) {
            if (primitive == hit.primitive)
                continue;
            bool hit = primitive->hit(shadowRay, tmp);
            if (hit && tmp.distance > 0 && tmp.distance < distance) {
                return Vector3D(0, 0, 0);
            }
        }

        Vector3D newColor = color * _color * (_intensity * 0.01);
        newColor.clamp(0, 255);

        double diffuseIntensity = std::max(0.0, angle);
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
