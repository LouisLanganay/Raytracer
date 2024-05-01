/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** RenderBuilder
*/

#ifndef RENDERBUILDER_HPP_
#define RENDERBUILDER_HPP_

#include <memory>
#include <string>
#include <libconfig.h++>

namespace RayTracer::Builders {
    class RenderBuilder {
        private:
            std::string _filename;
            std::string _type;
            double _maxDepth;
            double _samples;
        public:
            RenderBuilder() {}

            RenderBuilder &set(const std::string &key, const libconfig::Setting &setting)
            {
                if (key == "filename")
                    setting.lookupValue("filename", _filename);
                if (key == "type")
                    setting.lookupValue("type", _type);
                return *this;
            }

            RenderBuilder &set(const std::string &key, double value)
            {
                if (key == "maxDepth")
                    _maxDepth = value;
                if (key == "samples")
                    _samples = value;
                return *this;
            }

            std::string getFilename() const { return _filename; }
            std::string getType() const { return _type; }
            double getMaxDepth() const { return _maxDepth; }
            double getSamples() const { return _samples; }

    };
}

#endif /* !RENDERBUILDER_HPP_ */
