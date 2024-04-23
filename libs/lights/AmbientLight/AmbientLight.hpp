/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** AmbientLight
*/

#ifndef AmbientLIGHT_HPP_
#define AmbientLIGHT_HPP_

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

#endif /* !AmbientLIGHT_HPP_ */
