/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Render
*/

#include "Render.hpp"

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

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                printf("x: %d, y: %d\n", x, y);
                // Ray ray = camera->generateRay(x, y);
                // Color color = trace(ray);
                // setPixel(x, y, color);
            }
        }
    }
}
