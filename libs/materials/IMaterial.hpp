/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** IMaterial
*/

#ifndef IMATERIAL_HPP_
#define IMATERIAL_HPP_

#include "../../src/Vector/Vector3D.hpp"
#include "../../src/Ray/Ray.hpp"
#include "../../src/Ray/RayHit.hpp"
#include <string>

class HitRecord;

struct Scatter {
    Ray reflected;
    Vector3D attenuation;
    Vector3D specularReflection;
    double reflectionIndex;
    double transmissionIndex;
};

namespace RayTracer::Materials {


    class IMaterial {
        public:
            virtual ~IMaterial() = default;

            virtual void setColor(double r, double g, double b) = 0;
            virtual void setName(const std::string &name) = 0;
            virtual Vector3D getColor(const Ray &ray, const HitRecord &hit) const = 0;

            virtual std::string getName() const = 0;
            // GetColor
            virtual Vector3D getColor() const = 0;

            virtual bool scatter(const Ray &ray, const HitRecord &rec, Vector3D &attenuation, Ray &scattered) const = 0;
        protected:
        private:
    };
}

#endif /* !IMATERIAL_HPP_ */
