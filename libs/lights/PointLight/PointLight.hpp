/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** PointLight
*/

#ifndef POINTLIGHT_HPP_
#define POINTLIGHT_HPP_

#include <iostream>
#include "../ALight.hpp"

namespace RayTracer::Lights {

    class PointLight : public ALight {
        public:
            PointLight();
            ~PointLight() = default;

            Vector3D computeLights(
                Vector3D color,
                const Ray &ray,
                // const RayHit &hit,
                const HitRecord &hit,
                const std::vector<RayTracer::Primitives::IPrimitive *> &primitives
            ) const override;

            Vector3D computeShadowIntensity(
                Vector3D color,
                const Ray &ray,
                // const RayHit &hit,
                const HitRecord &hit,
                const std::vector<RayTracer::Primitives::IPrimitive *> &primitives
            ) const;

        protected:
        private:
    };
}

#endif /* !POINTLIGHT_HPP_ */
