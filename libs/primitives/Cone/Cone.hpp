/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cone
*/

#ifndef CONE_HPP_
#define CONE_HPP_

#include "../APrimitive.hpp"

namespace RayTracer::Primitives {
    class Cone : public APrimitive {
        public:
            Cone();
            ~Cone();

            bool hit(const Ray& ray, RayHit& hit) override;
        protected:
        private:
            Point3D _center;
            Matrix _transformation;
            bool _isCenterSet = false;
    };
}

#endif /* !CONE_HPP_ */
