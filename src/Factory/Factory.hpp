/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Factory
*/

#ifndef FACTORY_HPP_
#define FACTORY_HPP_

#include <memory>
#include <map>
#include "../DLLoader.hpp"

namespace RayTracer {

    template<typename T>
    class Factory {
        public:
            Factory() = default;
            ~Factory() = default;

            std::unique_ptr<T> create(const std::string &type)
            {
                if(_plugins.find(type) == _plugins.end())
                    return nullptr;
                DLLoader<T> *loader = _plugins[type].get();
                return loader->getInstance();
            }

            void addPlugin(const std::string &type, std::unique_ptr<DLLoader<T>> &plugin)
            {
                if (_plugins.find(type) != _plugins.end())
                    return;
                _plugins.emplace(type, std::move(plugin));
            }
        protected:
        private:
            std::map<std::string, std::unique_ptr<DLLoader<T>>> _plugins;
    };
}

#endif /* !FACTORY_HPP_ */
