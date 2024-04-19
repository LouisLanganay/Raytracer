/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Parser
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <libconfig.h++>
#include "Scene.hpp"
#include <memory>
#include "LibLoader.hpp"

namespace RayTracer {
    class Parser {
        public:
            Parser(const char *filename, LibLoader &loader);
            ~Parser() = default;

            void parse();
            void parseCamera(const libconfig::Setting& setting);
            void parseLights(const libconfig::Setting& setting);
            void parseLight(const libconfig::Setting& setting);
            void parsePrimitives(const libconfig::Setting& setting);
            void parsePrimitive(const libconfig::Setting& setting);

            std::unique_ptr<Scene> &getScene();

        protected:
        private:
            const char *_filename;
            LibLoader &_libLoader;
            std::unique_ptr<Scene> _scene;
            libconfig::Config cfg;

            double parseDouble(const libconfig::Setting& setting);
    };
}

#endif /* !PARSER_HPP_ */