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
        _startTime = time(0);
    }

    void ARender::setFilename(const std::string &filename)
    {
        _filename = filename;
    }

    void ARender::updateProgress(int pixelsRendered, int totalPixels, std::string message)
    {
        double progress = static_cast<double>(pixelsRendered) / totalPixels;

        if (_lastProgress + 0.01 > progress & progress != 1.0)
            return;
        _lastProgress = progress;

        if (message != _message && _message != "")
            std::cout << std::endl;

        std::cout << "\r" << message << " [";
        int barWidth = 50;
        int pos = static_cast<int>(barWidth * progress);
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) {
                if (progress < 0.5)
                    std::cout << "\033[31m";
                else if (progress < 0.99)
                    std::cout << "\033[33m";
                else
                    std::cout << "\033[32m";
                std::cout << "=";
            }
            else if (i == pos) {
                if (progress < 0.5)
                    std::cout << "\033[31m>";
                else if (progress < 0.99)
                    std::cout << "\033[33m>";
                else
                    std::cout << "\033[32m>";
            }
            else
                std::cout << " ";
        }
        std::cout << "\033[0m] " << std::fixed << std::setprecision(2) << progress * 100.0 << "%";
        std::cout << " - (" << pixelsRendered << "/" << totalPixels << ")";

        if (progress > 0) {
            time_t currentTime = time(0);
            int elapsedTime = currentTime - _startTime;
            int remainingTime = static_cast<int>(elapsedTime / progress) - elapsedTime;

            std::cout << " - Remaining time: ";
            int hours = remainingTime / 3600;
            int minutes = (remainingTime % 3600) / 60;
            remainingTime = remainingTime % 60;
            if (hours > 0) {
                if (hours < 10) std::cout << "0";
                std::cout << hours << ":";
            }
            if (minutes < 10) std::cout << "0";
            std::cout << minutes << ":";
            if (remainingTime < 10) std::cout << "0";
            std::cout << remainingTime;
        }
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

        tmp.distance = std::numeric_limits<double>::max();
        rayHit.distance = std::numeric_limits<double>::max();
        for (Primitives::IPrimitive *primitive : scene.getPrimitives()) {
            if (primitive == lastPrimitive)
                continue;
            bool hit = primitive->hit(ray, tmp);
            if (hit && tmp.distance > 0 && (closest == nullptr || tmp.distance < rayHit.distance)) {
                rayHit = tmp;
                rayHit.primitive = primitive;
                closest = primitive;
            }
        }
        if (closest == nullptr)
            return Vector3D(0, 0, 0);
        Vector3D color;
        color._x = rayHit.primitive->getMaterial()->getColor()._x;
        color._y = rayHit.primitive->getMaterial()->getColor()._y;
        color._z = rayHit.primitive->getMaterial()->getColor()._z;
        return color;
    }
}
