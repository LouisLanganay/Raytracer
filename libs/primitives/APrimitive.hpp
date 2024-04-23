/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** APrimitive
*/

#ifndef APRIMITIVE_HPP_
#define APRIMITIVE_HPP_

#include "IPrimitive.hpp"
#include <string>
#include "../../src/Point/Point3D.hpp"

namespace RayTracer::Primitives {

    class APrimitive : public IPrimitive {
        public:
            virtual ~APrimitive() = default;

            void setType(const std::string &type) override;
            void setOrigin(int x, int y, int z) override;
            void setRotation(int x, int y, int z) override;
            void setColor(int x, int y, int z) override;
            void setRadius(double radius) override;
            void setTransparency(double transparency) override;
            void setReflection(double reflection) override;
            void setAxis(RayTracer::Primitives::Axis axis) override;

            std::string getType() const override;
            Point3D getOrigin() const override;
            Point3D getRotation() const override;
            Point3D getColor() const override;
            double getRadius() const override;
            double getTransparency() const override;
            double getReflection() const override;
            RayTracer::Primitives::Axis getAxis() const override;

            virtual bool hit(const Ray& ray, RayHit& hit) const = 0;

        protected:
            std::string _type;
            Point3D _origin;
            Point3D _rotation;
            Point3D _color;
            double _radius;
            double _transparency;
            double _reflection;
            Axis _axis;
        private:
    };
}

#endif /* !APRIMITIVE_HPP_ */
