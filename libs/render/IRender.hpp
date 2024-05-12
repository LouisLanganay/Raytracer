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
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

namespace RayTracer::Render {

    class IRender {
        public:
            IRender() = default;
            virtual ~IRender() = default;

            virtual void render(Scene &Scene) = 0;
            virtual void setFilename(const std::string &filename) = 0;
            virtual void setMaxDepth(int maxDepth) = 0;
            virtual void setSamples(int samples) = 0;

            virtual int getMaxDepth() const = 0;
            virtual int getSamples() const = 0;
            virtual sf::Image renderVideo(Scene &scene, Camera &camera) = 0;
            virtual sf::Image renderPreview(Scene &scene, Camera &camera) = 0;
        protected:
        private:
    };
}

#endif /* !IRENDER_HPP_ */
