/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** DirectionalLight
*/

#ifndef DIRECTIONALLIGHT_HPP_
#define DIRECTIONALLIGHT_HPP_

#include <iostream>
#include "../ALight.hpp"

namespace RayTracer::Lights {

    class DirectionalLight : public ALight {
        public:
            DirectionalLight();
            ~DirectionalLight() = default;

            bool computeLights(const Point3D &point,
                                const Vector3D &normal,
                                Vector3D &color,
                                double &intensity,
                                const std::vector<RayTracer::Primitives::IPrimitive *> &primitives) override;
        protected:
        private:
    };
}

#endif /* !DIRECTIONALLIGHT_HPP_ */
