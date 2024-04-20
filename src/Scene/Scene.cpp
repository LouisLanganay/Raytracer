/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Scene
*/

#include "Scene.hpp"
#include <iostream>

namespace RayTracer {

    Scene::Scene()
    {
    }

    Scene::~Scene()
    {
    }

    void Scene::addPrimitive(std::unique_ptr<Primitives::IPrimitive> &primitive)
    {
        _primitives.push_back(primitive.release());
    }

    void Scene::addLight(std::unique_ptr<Lights::ILight> &light)
    {
        _lights.push_back(light.release());
    }

    void Scene::setCamera(std::unique_ptr<Camera> &camera)
    {
        _camera = camera.release();
    }

    const std::vector<Primitives::IPrimitive *> &Scene::getPrimitives() const
    {
        return _primitives;
    }

    const std::vector<Lights::ILight *> &Scene::getLights() const
    {
        return _lights;
    }

    const Camera *Scene::getCamera() const
    {
        return _camera;
    }

    Vector3D Scene::traceRay(const Ray &ray) const
    {
        Vector3D color(0, 0, 0);
        for (const auto &primitive : _primitives) {
            bool hit = primitive->hit(ray);
            if (hit) {
                color._x = primitive->getColor()._x;
                color._y = primitive->getColor()._y;
                color._z = primitive->getColor()._z;
            }
        }
        return color;
    }

    void Scene::setPixel(int x, int y, Vector3D &color)
    {
        int ir = static_cast<int>(color._x);
        int ig = static_cast<int>(color._y);
        int ib = static_cast<int>(color._z);

        std::cout << ir << " " << ig << " " << ib << std::endl;
    }
}
