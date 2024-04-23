/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Exceptions
*/

#ifndef EXCEPTIONS_HPP_
#define EXCEPTIONS_HPP_

#include <exception>
#include <string>

namespace RayTracer {
    class Exception : public std::exception {
        public:
            Exception(const std::string &message) : _message(message) {}
            const char *what() const noexcept override { return _message.c_str(); }

        protected:
        private:
            std::string _message;
    };

    class MainException : public Exception {
        public:
            MainException(const std::string &message) : Exception(message) {}
    };

    class LoaderException : public Exception {
        public:
            LoaderException(const std::string &message) : Exception(message) {}
    };

    class ParserException : public Exception {
        public:
            ParserException(const std::string &message) : Exception(message) {}
    };

    class CameraException : public Exception {
        public:
            CameraException(const std::string &message) : Exception(message) {}
    };

    class LightException : public Exception {
        public:
            LightException(const std::string &message) : Exception(message) {}
    };

    class PrimitiveException : public Exception {
        public:
            PrimitiveException(const std::string &message) : Exception(message) {}
    };
}
#endif /* !EXCEPTIONS_HPP_ */
