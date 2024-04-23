/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** AMaterial
*/

#include "AMaterial.hpp"

namespace RayTracer::Materials {
    void AMaterial::setColor(double r, double g, double b)
    {
        _color = Vector3D(r, g, b);
    }

    Vector3D AMaterial::getColor() const
    {
        return _color;
    }

    void AMaterial::setName(const std::string &name)
    {
        _name = name;
    }

    std::string AMaterial::getName() const
    {
        return _name;
    }
}
