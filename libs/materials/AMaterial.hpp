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
#include <string>

namespace RayTracer::Materials {
    class AMaterial : public IMaterial {
        public:
            virtual ~AMaterial() = default;

            void setColor(double r, double g, double b) override;
            void setName(const std::string &type) override;

            Vector3D getColor() const override;
            std::string getName() const override;

        protected:
            Vector3D _color;
            std::string _name;
        private:
    };
}

#endif /* !AMATERIAL_HPP_ */
