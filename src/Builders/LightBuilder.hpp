/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** LightBuilder
*/

#ifndef LIGHTBUILDER_HPP_
#define LIGHTBUILDER_HPP_

#include "Point3D.hpp"
#include <iostream>
#include <memory>
#include <string>
#include "../../libs/lights/ALight.hpp"

namespace RayTracer::Builders {
    class LightBuilder {
        private:
            Lights::ILight *_light;

        public:
            LightBuilder(RayTracer::Lights::ILight *light)
            {
                _light = light;
            }

            LightBuilder& set(const std::string &key, Point3D value)
            {
                if (key == "position")
                    _light->setOrigin(value._x, value._y, value._z);
                return *this;
            }

            LightBuilder& set(const std::string &key, Vector3D value)
            {
                if (key == "color")
                    _light->setColor(value._x, value._y, value._z);
                if (key == "direction")
                    _light->setDirection(value._x, value._y, value._z);
                return *this;
            }

            LightBuilder& set(const std::string &key, double value)
            {
                if (key == "intensity")
                    _light->setIntensity(value);
                return *this;
            }

            LightBuilder& set(const std::string &key, const std::string &value)
            {
                if (key == "type")
                    _light->setType(value);
                return *this;
            }
    };
}

#endif /* !LIGHTBUILDER_HPP_ */
