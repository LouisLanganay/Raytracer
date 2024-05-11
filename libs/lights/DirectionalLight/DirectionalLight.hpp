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

            Vector3D computeLights(
                Vector3D color,
                const Ray &ray,
                // const RayHit &hit,
                const HitRecord &hit,
                const std::vector<RayTracer::Primitives::IPrimitive *> &primitives
            ) const override;
        protected:
        private:
    };
}

#endif /* !DIRECTIONALLIGHT_HPP_ */
