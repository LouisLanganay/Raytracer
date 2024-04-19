/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Scene
*/

#include "Scene.hpp"

namespace RayTracer {

    Scene::Scene()
    {
    }

    Scene::~Scene()
    {
    }

    void Scene::addPrimitive(std::unique_ptr<Primitives::IPrimitive> &primitive)
    {
        _primitives.push_back(primitive.get());
    }

    void Scene::addLight(std::unique_ptr<Lights::ILight> &light)
    {
        _lights.push_back(light.get());
    }

    void Scene::setCamera(std::unique_ptr<Camera> &camera)
    {
        _camera = camera.release();
    }

    const std::vector<Primitives::IPrimitive *> Scene::getPrimitives() const
    {
        return _primitives;
    }

    const std::vector<Lights::ILight *> Scene::getLights() const
    {
        return _lights;
    }

    const Camera *Scene::getCamera() const
    {
        return _camera;
    }
}
