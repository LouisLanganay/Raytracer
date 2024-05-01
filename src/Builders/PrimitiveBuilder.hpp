/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** PrimitiveBuilder
*/

#ifndef PRIMITIVEBUILDER_HPP_
#define PRIMITIVEBUILDER_HPP_

#include "Point3D.hpp"
#include <iostream>
#include <memory>
#include <string>
#include "../../libs/primitives/APrimitive.hpp"
#include "Exceptions.hpp"
#include <libconfig.h++>


namespace RayTracer::Builders {
    class PrimitiveBuilder {
        private:
            Primitives::IPrimitive *_primitive;

        public:
            PrimitiveBuilder(RayTracer::Primitives::IPrimitive *primitive)
            {
                _primitive = primitive;
            }

            PrimitiveBuilder& set(const std::string &key, Point3D value)
            {
                if (key == "position")
                    _primitive->setOrigin(value._x, value._y, value._z);
                if (key == "rotation")
                    _primitive->setRotation(Vector3D(value._x, value._y, value._z));
                if (key == "scale")
                    _primitive->setScale(Vector3D(value._x, value._y, value._z));
                if (key == "translation")
                    _primitive->setTranslation(Vector3D(value._x, value._y, value._z));
                return *this;
            }

            PrimitiveBuilder& set(const std::string &key, double value)
            {
                if (key == "radius")
                    _primitive->setRadius(value);
                if (key == "height")
                    _primitive->setHeight(value);
                if (key == "width")
                    _primitive->setWidth(value);
                return *this;
            }

            PrimitiveBuilder& set(const std::string &key, const std::string &value)
            {
                if (key == "type")
                    _primitive->setType(value);
                return *this;
            }

            PrimitiveBuilder& set(const std::string &key, const libconfig::Setting &setting)
            {
                if (key == "axis") {
                    std::string arg = setting["axis"];
                    if (arg == "Z")
                        _primitive->setAxis(RayTracer::Primitives::Axis::Z);
                    else if (arg == "Y")
                        _primitive->setAxis(RayTracer::Primitives::Axis::Y);
                    else if (arg == "X")
                        _primitive->setAxis(RayTracer::Primitives::Axis::X);
                    else
                        throw ParserException("Unknown axis");
                }
                return *this;
            }

            PrimitiveBuilder& set(const std::string &key, const std::shared_ptr<RayTracer::Materials::IMaterial> &value)
            {
                if (key == "material")
                    _primitive->setMaterial(value);
                return *this;
            }
    };
}

#endif /* !PRIMITIVEBUILDER_HPP_ */
