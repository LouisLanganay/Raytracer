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

#endif /* !AmbientLIGHT_HPP_ */
