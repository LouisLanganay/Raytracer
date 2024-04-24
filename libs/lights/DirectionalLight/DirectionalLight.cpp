/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** DirectionalLight
*/

#include "DirectionalLight.hpp"
#include "../../../src/Loader/LibLoader.hpp"
#define M_PI 3.14159265358979323846

namespace RayTracer::Lights
{
    DirectionalLight::DirectionalLight()
    {
    }

    bool DirectionalLight::computeLights(const Point3D &point,
        const Vector3D &normal,
        Vector3D &color,
        double &intensity,
        const std::vector<RayTracer::Primitives::IPrimitive *> &primitives)
    {
        Vector3D lightDir = getOrigin() - point;
        lightDir.normalize();
        Point3D startPoint = point;
        double angle = acos(lightDir.dot(normal));

        if (angle > (M_PI / 2.0)) {
            color += _color;
            intensity = 0.0;
            return false;
        } else {
            intensity = _intensity * (1.0 - (angle / (M_PI / 2.0)));
            color += _color * intensity;
            return true;
        }
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
