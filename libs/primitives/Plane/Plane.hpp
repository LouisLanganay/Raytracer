/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Plane
*/

#ifndef PLANE_HPP_
#define PLANE_HPP_

#include "../APrimitive.hpp"

namespace RayTracer::Primitives {
    class Plane : public APrimitive {
        public:
            Plane();
            ~Plane();

            bool hit(const Ray& ray, RayHit& hit) override;

        protected:
        private:
            Point3D _center;
    };
}

#endif /* !PLANE_HPP_ */