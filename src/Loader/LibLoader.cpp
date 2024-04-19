/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** LibLoader
*/

#include "LibLoader.hpp"
#include <filesystem>

namespace RayTracer {
    void LibLoader::loadPlugins()
    {
        std::string path = "./libs/";

        for (const auto& entry : std::filesystem::recursive_directory_iterator(path)) {
            if (std::filesystem::is_regular_file(entry) && entry.path().extension() == ".so") {
                RayTracer::PluginType type = RayTracer::PluginType::LIGHT;

                DLLoader<RayTracer::PluginType> typeLoader(entry.path());
                typeLoader.loadInstance("getTypePoint");
                type = *(typeLoader.getInstance().get());

                switch (type) {
                    case RayTracer::PluginType::LIGHT:
                        loadPlugin(_lightFactory, entry.path());
                        break;
                    case RayTracer::PluginType::PRIMITIVE:
                        loadPlugin(_primitiveFactory, entry.path());
                        break;
                    default:
                        break;
                }
                std::cout << "Plugin " << entry.path() << " loaded" << std::endl;
            }
        }
    }

    Factory<RayTracer::Lights::ILight> &LibLoader::getLightFactory()
    {
        return _lightFactory;
    }

    Factory<RayTracer::Primitives::IPrimitive> &LibLoader::getPrimitiveFactory()
    {
        return _primitiveFactory;
    }
}