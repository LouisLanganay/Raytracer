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
            void setPosition(double x, double y, double z) override;

            std::string getType() const override;
            Point3D getOrigin() const override;
            Vector3D getColor() const override;
            Point3D getPosition() const override;
            double getIntensity() const override;

            virtual bool computeLights(const Point3D &point,
                                        const Vector3D &normal,
                                        Vector3D &color,
                                        double &intensity,
                                        const std::vector<RayTracer::Primitives::IPrimitive *> &primitives) = 0;
        protected:
            std::string _type;
            Point3D _origin;
            Vector3D _color;
            Point3D _position;
            double _intensity;
        private:
    };
}

#endif /* !ALIGHT_HPP_ */
