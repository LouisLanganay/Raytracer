/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** ARender
*/

#ifndef ARENDER_HPP_
#define ARENDER_HPP_

#include "IRender.hpp"
#include "../../src/Camera/Camera.hpp"
#include <memory>

namespace RayTracer::Render {

    class ARender : public IRender {
        public:
            ARender();
            virtual ~ARender() = default;

            virtual void render(Scene &scene) = 0;
            void setFilename(const std::string &filename) override;

        protected:
            std::string _filename;
            void updateProgress(int pixelsRendered, int totalPixels);
        private:
    };

}


#endif /* !ARENDER_HPP_ */
