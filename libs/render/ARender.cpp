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
        double intensity;
        Vector3D color = Vector3D(0, 0, 0);
        bool validIllum = false;

        tmp.distance = std::numeric_limits<double>::max();
        rayHit.distance = std::numeric_limits<double>::max();
        for (Primitives::IPrimitive *primitive : scene.getPrimitives()) {
            if (primitive == lastPrimitive)
                continue;
            color = primitive->getMaterial().get()->getColor();
            bool hit = primitive->hit(ray, tmp);
            if (hit && tmp.distance > 0 && (closest == nullptr || tmp.distance < rayHit.distance)) {
                rayHit = tmp;
                rayHit.primitive = primitive;
                closest = primitive;
                for (Lights::ILight *_light : scene.getLights()) {
                    validIllum = _light->computeLights(tmp.point, tmp.normal, color, intensity, scene.getPrimitives());
                }
            if (validIllum) {
                return color;
            }
            }
        }
        if (closest == nullptr)
            return Vector3D(0, 0, 0);
        return color;
    }
}
