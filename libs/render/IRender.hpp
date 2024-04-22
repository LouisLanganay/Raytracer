/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** IRender
*/

#ifndef IRENDER_HPP_
#define IRENDER_HPP_

#include "../../src/Camera/Camera.hpp"
#include "../../src/Scene/Scene.hpp"

namespace RayTracer::Render {

    class IRender {
        public:
            IRender() = default;
            ~IRender() = default;

            virtual void render(Scene &Scene) = 0;
            virtual void setFilename(const std::string &filename) = 0;

        protected:
        private:
    };
}

#endif /* !IRENDER_HPP_ */