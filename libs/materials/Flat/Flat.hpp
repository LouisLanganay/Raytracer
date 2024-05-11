/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Flat
*/

#ifndef FLAT_HPP_
#define FLAT_HPP_

#include "../AMaterial.hpp"

namespace RayTracer {
    class Ray;
    class HitRecord;
    class Vector3D;
}

namespace RayTracer::Materials {

    class Flat : public AMaterial {
        public:
            Flat() = default;
            ~Flat() override = default;

            bool scatter(const Ray &ray, HitRecord &rec, Vector3D &attenuation, Ray &scattered) const override;
            Vector3D getColor(const Ray &ray, const HitRecord &hit) override;
        private:
            // Add any private members here if needed
    };

}

#endif /* !FLAT_HPP_ */
