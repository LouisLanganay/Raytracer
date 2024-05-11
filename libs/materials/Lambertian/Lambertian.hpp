/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Lambertian
*/

#ifndef LAMBERTIAN_HPP_
#define LAMBERTIAN_HPP_

#include "../AMaterial.hpp"

namespace RayTracer::Materials {
    class Lambertian : public AMaterial {
        public:
            Lambertian();
            ~Lambertian();

            bool scatter(const Ray &ray, const RayHit &hit, Scatter &scatter) const override;
            Vector3D getColor(const Ray &ray, const RayHit &hit) const override;
        protected:
        private:
    };
}

#endif /* !LAMBERTIAN_HPP_ */
