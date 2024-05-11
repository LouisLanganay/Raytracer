/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** AMAterial
*/

#ifndef AMATERIAL_HPP_
#define AMATERIAL_HPP_

#include "IMaterial.hpp"
#include "../../src/Vector/Vector3D.hpp"
#include "../../src/Ray/Ray.hpp"
#include "../../src/Ray/RayHit.hpp"
#include <string>

class HitRecord;

namespace RayTracer::Materials {
    class AMaterial : public IMaterial {
        public:
            virtual ~AMaterial() = default;

            void setColor(double r, double g, double b) override;
            void setName(const std::string &type) override;
            virtual Vector3D getColor(const Ray &ray, const HitRecord &hit) const = 0;

            Vector3D getColor() const override;
            std::string getName() const override;

            virtual bool scatter(const Ray &ray, HitRecord &rec, Vector3D &attenuation, Ray &scattered) const = 0;
        protected:
            std::string _name;
            Vector3D _color;
        private:
    };
}

#endif /* !AMATERIAL_HPP_ */
