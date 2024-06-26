/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** ARender
*/

#include "ARender.hpp"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>

namespace RayTracer::Render {
    ARender::ARender()
    {
        _startTime = time(0);
        _seed = static_cast<std::size_t>(time(nullptr));
        _quality = 1;
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
    ) {
        Primitives::IPrimitive *closest = nullptr;
        RayHit tmp;
        RayHit rayHit;
        Vector3D color(0, 0, 0);
        RayTracer::Materials::Scatter scatter;
        Vector3D finalColor(0, 0, 0);
        Ray ShadowRay;

        tmp.distance = std::numeric_limits<double>::max();
        rayHit.distance = std::numeric_limits<double>::max();
        for (Primitives::IPrimitive *primitive: scene.getPrimitives()) {
            if (primitive == lastPrimitive)
                continue;
            bool hit = primitive->hit(ray, tmp);
            if (hit && tmp.distance > 0 && (closest == nullptr || tmp.distance < rayHit.distance)) {
                rayHit = tmp;
                rayHit.primitive = primitive;
                closest = primitive;
            }
        }
        if (!closest)
            return Vector3D(0, 0, 0);
        std::shared_ptr<RayTracer::Materials::IMaterial> material = closest->getMaterial();
        if (depth > 0 && material->scatter(ray, rayHit, scatter)) {
            //Vector3D reflectedColor;
            //for (std::size_t i = 0; i < 3; i++) {
            //    Point3D reflectedOrigin = scatter.reflected.getOrigin() + scatter.reflected.getDirection() * 0.001;
            //    reflectedOrigin += randomInUnitSphere() * 0.1;
            //    Ray reflectedRay(reflectedOrigin, scatter.reflected.getDirection());
            //    reflectedColor += castRay(scatter.reflected, scene, depth - 1, closest) * scatter.reflectionIndex;
            //}
            //reflectedColor /= 3;
            //reflectedColor.clamp(0, 255);
            //color = material->getColor(ray, rayHit) * scatter.attenuation * (1 - scatter.reflectionIndex);
            //color += reflectedColor * scatter.reflectionIndex * scatter.attenuation;
            color = material->getColor(ray, rayHit);
        } else {
            color = material->getColor(ray, rayHit);
        }
        color.clamp(0, 255);
        for (const auto &light: scene.getLights()) {
            Vector3D lightColor = light->computeLights(color, ray, rayHit, scene.getPrimitives());
            if (lightColor.length() > 0) {
                ShadowRay._origin = rayHit.point;
                ShadowRay._direction = light->getPosition() - rayHit.point;
                ShadowRay._direction.normalize();
                for (Primitives::IPrimitive *primitive: scene.getPrimitives()) {
                    if (primitive == rayHit.primitive)
                        continue;
                    if (primitive->hit(ShadowRay, tmp) && tmp.distance > 0 && tmp.distance < ShadowRay._direction.length()) {
                        lightColor = Vector3D(0, 0, 0);
                        break;
                    }
                }
            }
            finalColor += lightColor;
        }
        return finalColor;
    }

    void ARender::setMaxDepth(int maxDepth)
    {
        _maxDepth = maxDepth;
    }

    void ARender::setSamples(int samples)
    {
        _samples = samples;
    }

    void ARender::setQuality(int quality)
    {
        _quality = quality;
    }

    int ARender::getMaxDepth() const
    {
        return _maxDepth;
    }

    int ARender::getSamples() const
    {
        return _samples;
    }

    int ARender::getQuality() const 
    {
        return _quality;
    }

    void ARender::log(const std::string &message)
    {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);

        std::tm* local_time = std::localtime(&now_time);

        std::ostringstream oss;
        oss << std::put_time(local_time, "%Y-%m-%d %H:%M:%S");

        std::cout << "[" << oss.str() << "] " << message << std::endl;
    }

}
