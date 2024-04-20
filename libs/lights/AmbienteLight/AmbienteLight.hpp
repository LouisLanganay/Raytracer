/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** AmbienteLight
*/

#ifndef AMBIENTELIGHT_HPP_
#define AMBIENTELIGHT_HPP_

#include "../ALight.hpp"

namespace RayTracer::Lights {
    class AmbientLight : public ALight {
        public:
            AmbientLight();
            ~AmbientLight();

        protected:
        private:
    };
}

#endif /* !AMBIENTELIGHT_HPP_ */
