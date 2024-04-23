/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** LibLoader
*/

#ifndef LIBLOADER_HPP_
#define LIBLOADER_HPP_

#include "../Factory/Factory.hpp"
#include "../../libs/lights/ILight.hpp"
#include "../../libs/primitives/IPrimitive.hpp"
#include "../../libs/render/IRender.hpp"

namespace RayTracer {
    enum class PluginType {
        LIGHT,
        MATERIAL,
        PRIMITIVE,
        RENDER
    };

    class LibLoader {
        public:
            LibLoader() = default;
            ~LibLoader() = default;

            void loadPlugins();

            Factory<RayTracer::Lights::ILight> &getLightFactory();
            Factory<RayTracer::Primitives::IPrimitive> &getPrimitiveFactory();
            Factory<RayTracer::Render::IRender> &getRenderFactory();


            template<typename T>
            void loadPlugin(Factory<T> &factory, const std::string &path)
            {
                std::unique_ptr<DLLoader<T>> loader = std::make_unique<DLLoader<T>>(path);
                std::unique_ptr<DLLoader<std::string>> typeLoader = std::make_unique<DLLoader<std::string>>(path);

                loader->loadInstance("getEntryPoint");
                typeLoader->loadInstance("getNamePoint");
                factory.addPlugin((*typeLoader->getInstance()), loader);
            }
        protected:
        private:
            Factory<RayTracer::Lights::ILight> _lightFactory;
            Factory<RayTracer::Primitives::IPrimitive> _primitiveFactory;
            Factory<RayTracer::Render::IRender> _renderFactory;
    };
}

#endif /* !LIBLOADER_HPP_ */
