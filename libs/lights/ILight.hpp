/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** ILight
*/

#ifndef ILIGHT_HPP_
#define ILIGHT_HPP_

#include "../../src/Point/Point3D.hpp"
#include "../primitives/IPrimitive.hpp"
#include <memory>
#include <vector>
#include <string>

namespace RayTracer::Lights {
    class ILight {
        public:
            virtual ~ILight() = default;

            virtual void setType(const std::string &type) = 0;
            virtual void setOrigin(double x, double y, double z) = 0;
            virtual void setColor(double x, double y, double z) = 0;
            virtual void setIntensity(double intensity) = 0;
            virtual void setAttenuation(double attenuation) = 0;
            virtual void setPosition(double x, double y, double z) = 0;
            virtual void setDirection(double x, double y, double z) = 0;

            virtual std::string getType() const = 0;
            virtual Point3D getOrigin() const = 0;
            virtual Vector3D getColor() const = 0;
            virtual Point3D getPosition() const = 0;
            virtual double getAttenuation() const = 0;
            virtual double getIntensity() const = 0;
            virtual Vector3D getDirection() const = 0;

            virtual Vector3D computeLights(
                Vector3D color,
                const Ray &ray,
                const RayHit &hit,
                const std::vector<RayTracer::Primitives::IPrimitive *> &primitives
            ) const = 0;
        protected:
        private:
    };
}

#endif /* !ILIGHT_HPP_ */
