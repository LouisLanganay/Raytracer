/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Mirror
*/

#ifndef MIRROR_HPP_
#define MIRROR_HPP_

#include "../AMaterial.hpp"

namespace RayTracer::Materials {
    class Mirror : public AMaterial {
        public:
            Mirror();
            ~Mirror();

            bool scatter(const Ray &ray, const RayHit &hit, Scatter &scatter) const override;
            Vector3D getColor(const Ray &ray, const RayHit &hit) const override;
        protected:
        private:
    };
}

#endif /* !MIRROR_HPP_ */
