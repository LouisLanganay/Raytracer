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
#include "../../libs/primitives/IPrimitive.hpp"
#include "../../libs/lights/ILight.hpp"
#include "../Camera/Camera.hpp"

namespace RayTracer {
    class Scene {
        public:
            Scene();
            ~Scene();

            void addPrimitive(std::unique_ptr<Primitives::IPrimitive> &primitive);
            void addLight(std::unique_ptr<Lights::ILight> &light);
            void setCamera(std::unique_ptr<Camera> &camera);
            void setCamera(Camera *camera);

            const std::vector<Primitives::IPrimitive *> &getPrimitives() const;
            const std::vector<Lights::ILight *> &getLights() const;
            Camera *getCamera() const;
            void moveCamera(double x, double y, double z);

        protected:
        private:
            std::vector<Primitives::IPrimitive *> _primitives;
            std::vector<Lights::ILight *> _lights;
            Camera *_camera;
    };
}

#endif /* !SCENE_HPP_ */
