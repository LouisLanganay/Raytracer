/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Render
*/

#ifndef RENDER_HPP_
#define RENDER_HPP_

#include "Scene.hpp"

namespace RayTracer {
    class Render {
        public:
            Render(std::unique_ptr<Scene> &scene);
            ~Render();

            void render();

        protected:
        private:
            std::unique_ptr<Scene> _scene;
    };
}


#endif /* !RENDER_HPP_ */
