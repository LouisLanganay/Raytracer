/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cylinder
*/

#ifndef CYLINDER_HPP_
#define CYLINDER_HPP_

#include "../APrimitive.hpp"

namespace RayTracer::Primitives {
    class Cylinder : public APrimitive {
        public:
            Cylinder();
            ~Cylinder();

            bool hit(const Ray& ray, RayHit& hit) override;

        protected:
        private:
            Point3D _center;
    };
}

#endif /* !CYLINDER_HPP_ */
