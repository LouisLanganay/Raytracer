/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Sphere
*/

#ifndef PPMRENDER_HPP_
#define PPMRENDER_HPP_

#include "../ARender.hpp"
#include "../../../src/Camera/Camera.hpp"
#include <mutex>

namespace RayTracer::Render {
    class PPMRender : public ARender {
        public:
            PPMRender();
            virtual ~PPMRender() = default;

            virtual void render(Scene &scene) override;
        protected:
        private:
            std::vector<std::vector<Vector3D>> _image;
            std::mutex _mutex;
            int _pixelsRendered;

            void renderTile(Scene& scene, int start, int end, int width, int height, int samplesPerPixel);
    };

}


#endif /* !PPMRENDER_HPP_ */
