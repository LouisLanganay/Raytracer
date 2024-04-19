/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** DLLoader
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include <iostream>
#include <dlfcn.h>
#include <memory>

template <typename T>
class DLLoader {
    public:
        DLLoader(
            const std::string &path
        ) : _path(path)
        {
            _handle = dlopen(path.c_str(), RTLD_LAZY);
            if (!_handle) {
                std::cerr << "Cannot open library: " << dlerror() << std::endl;
                exit(84);
            }
        }

        ~DLLoader()
        {
            dlclose(_handle);
        }

        void loadInstance(const std::string &entryPoint)
        {
            _instance = reinterpret_cast<std::unique_ptr<T> (*)(void)>(dlsym(_handle, entryPoint.c_str()));
            if (!_instance) {
                std::cerr << "Cannot load symbol: " << dlerror() << std::endl;
                exit(84);
            }
        }

        std::unique_ptr<T> getInstance()
        {
            return _instance();
        }

    protected:
        const std::string &_path;
        void *_handle;
        std::unique_ptr<T> (*_instance)(void);
    private:
};

#endif /* !DLLOADER_HPP_ */
