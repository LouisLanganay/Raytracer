/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** ARender
*/

#include "ARender.hpp"
#include <iostream>
#include <iomanip>

namespace RayTracer::Render {
    ARender::ARender()
    {
        _light = new RayTracer::Lights::DirectionalLight();
        _light->setPosition(5.0, -10.0, -5.0);
        _light->setColor(1.0, 1.0, 1.0);
    }

    void ARender::setFilename(const std::string &filename)
    {
        _filename = filename;
    }

    void ARender::updateProgress(int pixelsRendered, int totalPixels, std::string message)
    {
        double progress = static_cast<double>(pixelsRendered) / totalPixels;

        if (message != _message && _message != "")
            std::cout << std::endl;

        std::cout << "\r" << message << " [";
        int barWidth = 50;
        int pos = static_cast<int>(barWidth * progress);
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) std::cout << "=";
            else if (i == pos) std::cout << ">";
            else std::cout << " ";
        }
        std::cout << "] " << std::fixed << std::setprecision(2) << progress * 100.0 << "% (" << pixelsRendered << "/" << totalPixels << ")";
        std::cout.flush();
        _message = message;
    }

    Vector3D ARender::castRay(double u, double v, const RayTracer::Scene &scene, std::size_t depth)
    {
        const RayTracer::Camera *camera = scene.getCamera();
        Ray ray = camera->generateRay(u, v);
        return castRay(ray, scene, depth);
    }

    Vector3D ARender::castRay(
        const Ray &ray,
        const RayTracer::Scene &scene,
        std::size_t depth,
        Primitives::IPrimitive *lastPrimitive
    )
    {
        Primitives::IPrimitive *closest = nullptr;
        RayHit tmp;
        RayHit rayHit;
        double intensity = 0;
        Point3D _color = Point3D(0, 0, 0);
        bool validIllum = false;

        tmp.distance = std::numeric_limits<double>::max();
        rayHit.distance = std::numeric_limits<double>::max();
        for (Primitives::IPrimitive *primitive : scene.getPrimitives()) {
            if (primitive == lastPrimitive)
                continue;
            bool hit = primitive->hit(ray, tmp);
            if (hit && tmp.distance > 0 && (closest == nullptr || tmp.distance < rayHit.distance)) {
                if (_light) {
                    validIllum = _light->computeLights(tmp.point, tmp.normal, _color, intensity, scene.getPrimitives(), primitive);
                }
                rayHit = tmp;
                rayHit.primitive = primitive;
                closest = primitive;
            }
        }
        if (closest == nullptr)
            return Vector3D(0, 0, 0);
        Vector3D color;
        if (validIllum) {

            color._x = _color._x * intensity;
            color._y = _color._y * intensity;
            color._z = _color._z * intensity;
            return color;
        } else {
            return Vector3D(0, 0, 0);
        }
        // color._x = rayHit.primitive->getColor()._x;
        // color._y = rayHit.primitive->getColor()._y;
        // color._z = rayHit.primitive->getColor()._z;
        // return color;
    }
}
