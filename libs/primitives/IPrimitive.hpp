/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** IPrimitive
*/

#ifndef IPRIMITIVE_HPP_
#define IPRIMITIVE_HPP_

#include "../../src/Point/Point3D.hpp"
#include "../../src/Ray/Ray.hpp"
#include <string>

namespace RayTracer::Primitives {
    enum Axis {
        Z,
        X,
        Y
    };

    class IPrimitive {
        public:
            virtual ~IPrimitive() = default;

            virtual void setType(const std::string &type) = 0;
            virtual void setOrigin(int x, int y, int z) = 0;
            virtual void setRotation(int x, int y, int z) = 0;
            virtual void setColor(int x, int y, int z) = 0;
            virtual void setRadius(double radius) = 0;
            virtual void setTransparency(double transparency) = 0;
            virtual void setReflection(double reflection) = 0;
            virtual void setAxis(RayTracer::Primitives::Axis axis) = 0;

            virtual std::string getType() const = 0;
            virtual Point3D getOrigin() const = 0;
            virtual Point3D getRotation() const = 0;
            virtual Point3D getColor() const = 0;
            virtual double getRadius() const = 0;
            virtual double getTransparency() const = 0;
            virtual double getReflection() const = 0;
            virtual RayTracer::Primitives::Axis getAxis() const = 0;

            virtual bool hit(const Ray& ray) const = 0;

        protected:
        private:
    };
}

#endif /* !IPRIMITIVE_HPP_ */
