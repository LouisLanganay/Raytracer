/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** ALight
*/

#ifndef ALIGHT_HPP_
#define ALIGHT_HPP_

#include "ILight.hpp"
#include <string>
#include "../../src/Point/Point3D.hpp"

namespace RayTracer::Lights {
    class ALight : public ILight {
        public:
            ~ALight() override = default;

            void setType(const std::string &type) override;
            void setOrigin(double x, double y, double z) override;
            void setColor(double x, double y, double z) override;
            void setIntensity(double intensity) override;
            void setAttenuation(double attenuation) override;
            void setPosition(double x, double y, double z) override;
            void setDirection(double x, double y, double z) override;

            std::string getType() const override;
            Point3D getOrigin() const override;
            Vector3D getColor() const override;
            double getAttenuation() const override;
            Point3D getPosition() const override;
            double getIntensity() const override;
            Vector3D getDirection() const override;

            virtual Vector3D computeLights(
                Vector3D color,
                const Ray &ray,
                const RayHit &hit,
                const std::vector<RayTracer::Primitives::IPrimitive *> &primitives
            ) const = 0;
        protected:
            std::string _type;
            Point3D _origin;
            Vector3D _color;
            Point3D _position;
            double _attenuation;
            double _intensity;
            Vector3D _direction;
        private:
    };
}

#endif /* !ALIGHT_HPP_ */
