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
        _type = getType();
        _color = getColor();
        _intensity = getIntensity();
    }

    bool DirectionalLight::computeLights(const Point3D &point,
        const Vector3D &normal,
        Point3D &color,
        double &intensity,
        const std::vector<RayTracer::Primitives::IPrimitive *> &primitives,
        Primitives::IPrimitive *currentPrimitive)
    {
        Vector3D lightDir = _origin - point;
        lightDir.normalize();
        Point3D startPoint = point;
        double angle = acos(lightDir.dot(normal));

        if (angle > M_PI / 2.0) {
            color = _color;
            intensity = 0.0;
            return false;
        } else {
            color = _color;
            intensity = _intensity * (1.0 - angle / (M_PI / 2.0));
            return true;
        }
    }
}
