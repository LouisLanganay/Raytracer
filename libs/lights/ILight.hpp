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
            virtual void setPosition(double x, double y, double z) = 0;

            virtual std::string getType() const = 0;
            virtual Point3D getOrigin() const = 0;
            virtual Point3D getColor() const = 0;
            virtual Point3D getPosition() const = 0;
            virtual double getIntensity() const = 0;

            virtual bool computeLights(const Point3D &point,
                                        const Vector3D &normal,
                                        Point3D &color,
                                        double &intensity,
                                        const std::vector<RayTracer::Primitives::IPrimitive *> &primitives,
                                        Primitives::IPrimitive *currentPrimitive) = 0;
        protected:
        private:
    };
}

#endif /* !ILIGHT_HPP_ */
