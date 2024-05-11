/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Scene
*/

#include "Scene.hpp"
#include <iostream>

typedef Vector3D Color;

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

    Camera *Scene::getCamera() const
    {
        return _camera;
    }

    Vector3D Scene::ray_Color(const Ray &r, int depth, const Scene &scene)
    {
        HitRecord rec;
        if (depth <= 0)
            return Color(0,0,0);

        if (scene.hit(r, Interval(0.001, infinity), rec)) {
            Ray scattered;
            Color attenuation;
            if (rec.material->scatter(r, rec, attenuation, scattered))
                return attenuation * ray_Color(scattered, depth-1, scene);
            return Color(0,0,0);
        }

        Vector3D unit_direction = Vector3D::unit_vector(r.getDirection());
        auto t = 0.5 * (unit_direction.getY() + 1.0);
        return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
    }

    bool Scene::hit(const Ray &r, const Interval interval, HitRecord &rec) const
    {
        HitRecord temp_rec;
        bool hit_anything = false;
        auto closest_so_far = interval.max();

        for (const auto &object : _primitives) {
            if (object->hit(r, Interval(interval.min(), closest_so_far), temp_rec)) {
                hit_anything = true;
                if (temp_rec.t < closest_so_far) {
                    closest_so_far = temp_rec.t;
                    rec = temp_rec;
                }
            }
        }
        return hit_anything;
    }    
}

void HitRecord::set_face_normal(const Ray &r, const Vector3D &outward_normal)
{
    front_face = r.getDirection().dot(outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
}