/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Flat
*/

#ifndef FLAT_HPP_
#define FLAT_HPP_

#include "../AMaterial.hpp"

namespace RayTracer::Materials {
    class Flat : public AMaterial {
        public:
            Flat();
            ~Flat();

            bool scatter(const Ray &ray, const RayHit &hit, Scatter &scatter) const override;
            Vector3D getColor(const Ray &ray, const RayHit &hit) const override;
        protected:
        private:
    };
}

#endif /* !FLAT_HPP_ */
