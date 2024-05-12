/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Sphere
*/

#ifndef PNGRENDER_HPP_
#define PNGRENDER_HPP_

#include "../ARender.hpp"
#include <mutex>

namespace RayTracer::Render {
    class PNGRender : public ARender {
        public:
            PNGRender();
            ~PNGRender();

            virtual void render(Scene &scene) override;
            virtual sf::Image renderVideo(Scene &scene, Camera &camera) override;
            virtual sf::Image renderPreview(Scene &scene, Camera &camera) override;
        protected:
        private:
            std::vector<std::vector<Vector3D>> _image;
            std::mutex _mutex;
            int _pixelsRendered;

            void renderTile(Scene& scene, int start, int end, int width, int height, int samplesPerPixel);
    };

}


#endif /* !PNGRENDER_HPP_ */
