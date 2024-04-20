/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Render
*/

#include "Render.hpp"
#include <iostream>

namespace RayTracer {
    Render::Render(std::unique_ptr<Scene> &scene) : _scene(scene.release())
    {
    }

    Render::~Render()
    {
    }

    void Render::render()
    {
        const Camera *camera = _scene->getCamera();
        int height = camera->getResolution()._y;
        int width = camera->getResolution()._x;

        std::cout << "P3\n" << width << " " << height << "\n255\n";
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                double u = static_cast<double>(x) / width;
                double v = static_cast<double>(y) / height;
                Ray ray = camera->generateRay(u, v);
                Vector3D color = _scene->traceRay(ray);
                _scene->setPixel(x, y, color);
            }
        }
    }
}
