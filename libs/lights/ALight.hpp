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

            std::string getType() const override;
            Point3D getOrigin() const override;
            Point3D getColor() const override;
            double getIntensity() const override;
        protected:
            std::string _type;
            Point3D _origin;
            Point3D _color;
            double _intensity;
        private:
    };
}

#endif /* !ALIGHT_HPP_ */
