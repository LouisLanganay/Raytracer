/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Sphere
*/

#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include "../APrimitive.hpp"

namespace RayTracer::Primitives {
    class Sphere : public APrimitive {
        public:
            Sphere();
            ~Sphere();

            bool hit(const Ray& ray, RayHit& hit) override;

        protected:
        private:
            Point3D _center;
    };
}

#endif /* !SPHERE_HPP_ */
