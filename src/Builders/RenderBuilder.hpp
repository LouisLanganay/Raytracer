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

namespace RayTracer::Builders {
    class RenderBuilder {
        private:
            std::string _filename;
            std::string _type;
        public:
            RenderBuilder() {}

            RenderBuilder &set(const std::string &key, const std::string &value)
            {
                if (key == "filename")
                    _filename = value;
                if (key == "type")
                    _type = value;
                return *this;
            }

        std::string getFilename() const { return _filename; }

    };
}

#endif /* !RENDERBUILDER_HPP_ */
