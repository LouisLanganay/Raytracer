/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Scene
*/

#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <vector>
#include <memory>
#include "IPrimitive.hpp"
#include "ILight.hpp"
#include "Camera.hpp"

namespace RayTracer {
    class Scene {
        public:
            Scene();
            ~Scene();

            void addPrimitive(std::unique_ptr<Primitives::IPrimitive> &primitive);
            void addLight(std::unique_ptr<Lights::ILight> &light);
            void setCamera(std::unique_ptr<Camera> &camera);

            const std::vector<Primitives::IPrimitive *> &getPrimitives() const;
            const std::vector<Lights::ILight *> &getLights() const;
            const Camera *getCamera() const;

            Vector3D traceRay(const Ray &ray) const;

            void setPixel(int x, int y, Vector3D &color);

        protected:
        private:
            std::vector<Primitives::IPrimitive *> _primitives;
            std::vector<Lights::ILight *> _lights;
            Camera *_camera;
    };
}

#endif /* !SCENE_HPP_ */
