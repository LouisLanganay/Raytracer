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
#include <math.h>

namespace RayTracer::Primitives {

    class APrimitive : public IPrimitive {
        public:
            APrimitive();
            virtual ~APrimitive() = default;

            void setType(const std::string &type) override;
            void setOrigin(double x, double y, double z) override;
            void setRadius(double radius) override;
            void setAxis(RayTracer::Primitives::Axis axis) override;
            void setMaterial(const std::shared_ptr<RayTracer::Materials::IMaterial> &material) override;
            void setHeight(double height) override;
            void setWidth(double width) override;

            std::string getType() const override;
            Point3D getOrigin() const override;
            Matrix getRotation() const override;
            double getRadius() const override;
            RayTracer::Primitives::Axis getAxis() const override;
            std::shared_ptr<RayTracer::Materials::IMaterial> getMaterial() const override;
            double getHeight() const override;
            double getWidth() const override;

            void setTranslation(const Vector3D &translation) override;
            void setRotation(const Vector3D &rotation) override;
            void setScale(const Vector3D &scale) override;
            Matrix getTransformationMatrix() const override;

            virtual bool hit(const Ray& ray, Interval interval, HitRecord& rec) = 0;


        protected:
            std::string _type;
            Point3D _origin;
            double _radius;
            Axis _axis;
            std::shared_ptr<RayTracer::Materials::IMaterial> _material;
            double _height;
            double _width;
        private:
            Matrix _translation;
            Matrix _rotation;
            Matrix _scale;
    };
}

#endif /* !APRIMITIVE_HPP_ */
