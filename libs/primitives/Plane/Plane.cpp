/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Plane
*/


#include "Plane.hpp"
#include "../../../src/Loader/LibLoader.hpp"
#include <memory>
#include <cmath>
#include <string.h>

#define M_PI 3.14159265358979323846
namespace RayTracer::Primitives {
    Plane::Plane()
    {
    }

    Plane::~Plane()
    {
    }

    bool Plane::hit(const Ray& ray, RayHit& hit)
    {
        _center = getOrigin();

        Vector3D direction;
        if (X == getAxis())
            direction = {1, 0, 0};
        else if (Y == getAxis())
            direction = {0, 1, 0};
        else if (Z == getAxis())
            direction = {0, 0, 1};
        else
            return false;

        Vector3D normal = direction.getNormalized();
        double produitScalaire = normal.dot(ray.getDirection());
        if (std::abs(produitScalaire) > 0.0001) {
            // hit.distance = la distance rayon a laquelle il touche la forme par rapport a l'origine du rayon
            //std::cout << "Center = " << _center._x  << " " << _center._y << " " << _center._z  << std::endl;
            //std::cout << "Origin = " << ray.getOrigin()._x << " " << ray.getOrigin()._y << " " << ray.getOrigin()._z << std::endl;
            //std::cout << "Normal = " << normal._x << " " << normal._y << " " << normal._z   << std::endl;
            //std::cout << "Result = " << (_center - ray.getOrigin()).dot(normal) << std::endl;
            hit.distance = (_center - ray.getOrigin()).dot(normal) / produitScalaire;
            if (hit.distance >= 0) {
                //std::cout << "HIT  " << hit.distance << std::endl;
                hit.point = ray.getPointAt(hit.distance);
                hit.normal = normal;
                return true;
            }
        }

        return false;
    }


    extern "C" std::unique_ptr<IPrimitive> getEntryPoint()
    {
        return std::make_unique<Plane>();
    }

    extern "C" std::unique_ptr<PluginType> getTypePoint()
    {
        return std::make_unique<PluginType>(PluginType::PRIMITIVE);
    }

    extern "C" std::unique_ptr<std::string> getNamePoint()
    {
        return std::make_unique<std::string>("plane");
    }
}
