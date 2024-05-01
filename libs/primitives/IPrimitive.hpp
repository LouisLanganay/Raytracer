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
#include "../../src/Ray/RayHit.hpp"
#include <string>
#include "../materials/IMaterial.hpp"
#include "../../src/Matrix/Matrix.hpp"
#include <memory>

namespace RayTracer::Primitives {
    enum Axis {
        Z,
        X,
        Y
    };

    class IPrimitive {
        public:
            IPrimitive() = default;
            virtual ~IPrimitive() = default;

            virtual void setType(const std::string &type) = 0;
            virtual void setOrigin(double x, double y, double z) = 0;
            virtual void setRadius(double radius) = 0;
            virtual void setAxis(RayTracer::Primitives::Axis axis) = 0;
            virtual void setMaterial(const std::shared_ptr<RayTracer::Materials::IMaterial> &material) = 0;
            virtual void setHeight(double height) = 0;
            virtual void setWidth(double width) = 0;

            virtual std::string getType() const = 0;
            virtual Point3D getOrigin() const = 0;
            virtual Matrix getRotation() const = 0;
            virtual double getRadius() const = 0;
            virtual RayTracer::Primitives::Axis getAxis() const = 0;
            virtual std::shared_ptr<RayTracer::Materials::IMaterial> getMaterial() const = 0;
            virtual double getHeight() const = 0;
            virtual double getWidth() const = 0;

            virtual void setTranslation(const Vector3D &translation) = 0;
            virtual void setRotation(const Vector3D &rotation) = 0;
            virtual void setScale(const Vector3D &scale) = 0;
            virtual Matrix getTransformationMatrix() const = 0;

            virtual bool hit(const Ray& ray, RayHit& hit) = 0;

        protected:
        private:
    };
}

#endif /* !IPRIMITIVE_HPP_ */
